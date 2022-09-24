#ifdef __cplusplus
extern "C" {
#endif//__cplusplus



#include <shengine/shEngine.h>

#include <gaia-universe-model/gaiaUniverseModel.h>
#include <shfd/shFile.h>

#include <json.h>
#include <inttypes.h>


uint8_t gaiaReadModelDescriptor(const char* path, GaiaModelDescriptorInfo* p_descriptor_info) {
	gaiaError(path == NULL, "invalid universe model descriptor info path", return 0);
	gaiaError(p_descriptor_info == NULL, "invalid universe model descriptor info memory", return 0);
	
	char* p_src = (char*)shReadText(path, NULL);
	gaiaError(p_src == NULL, "universe model descriptor not found", return 0);

	json_object* parser = json_tokener_parse(p_src);
	gaiaError(parser == NULL, "invalid compounds json format", return 0);
	free(p_src);

	json_object* json_source_range = json_object_object_get(parser, "source_range");
	gaiaError(json_source_range == NULL, "missing universe model source range", return 0);

	uint32_t range_items = (uint32_t)json_object_array_length(json_source_range);
	gaiaError(range_items < 2, "missing universe model source range data", return 0);
	
	json_object* json_range_start	= json_object_array_get_idx(json_source_range, 0);
	json_object* json_range_end		= json_object_array_get_idx(json_source_range, 1);

	p_descriptor_info->source_start = json_object_get_int(json_range_start);
	p_descriptor_info->source_end	= json_object_get_int(json_range_end);

	free(parser);

	return 1;
}

uint8_t gaiaWriteUniverseModelDescriptor(const char* path, uint32_t source_start, uint32_t source_end, const char* server) {
	gaiaError(path == NULL, "invalid destination file path", return 0);
	gaiaError(server == NULL, "invalid server address", return 0);

	FILE* dst_stream = fopen(path, "w");
	gaiaError(dst_stream == NULL, "universe model descriptor not found", return 0);

	char s_universe_model_descriptor[256] = { '\0' };

	sprintf(s_universe_model_descriptor, """{\n\
\"source_range\": [ %""" PRIu32 """, %""" PRIu32 """ ],\n\
\"server\": \"ftp://hihihiha\"\n\
}""", source_start, source_end);
	
	fwrite(s_universe_model_descriptor, 1, strlen(s_universe_model_descriptor), dst_stream);

	fclose(dst_stream);

	return 1;
}

uint8_t gaiaGetAvailableHeap(ShEngine* p_engine) {
	gaiaError(p_engine == NULL, "invalid engine memory", return 0);

	uint32_t host_visible_available_video_memory = 0;
	{
		uint32_t host_memory_type_index = 0;
		shGetMemoryType(
			p_engine->core.device,
			p_engine->core.physical_device,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			&host_memory_type_index
		);
		VkPhysicalDeviceMemoryBudgetPropertiesEXT heap_budget = { 0 };
		shGetMemoryBudgetProperties(p_engine->core.physical_device, NULL, NULL, &heap_budget);
		host_visible_available_video_memory = (uint32_t)heap_budget.heapBudget[host_memory_type_index];
	}

	uint32_t device_available_video_memory = 0;
	{
		uint32_t device_memory_type_index = 0;
		shGetMemoryType(
			p_engine->core.device,
			p_engine->core.physical_device,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			&device_memory_type_index
		);
		VkPhysicalDeviceMemoryBudgetPropertiesEXT heap_budget = { 0 };
		shGetMemoryBudgetProperties(p_engine->core.physical_device, NULL, NULL, &heap_budget);
		device_available_video_memory = (uint32_t)heap_budget.heapBudget[device_memory_type_index];
	}

	uint32_t available_gpu_heap = host_visible_available_video_memory <= device_available_video_memory ? host_visible_available_video_memory : device_available_video_memory;
	
	GaiaUniverseModelMemory* p_model = p_engine->p_ext;

	p_model->celestial_body_flags = GAIA_RA | GAIA_DEC | GAIA_BARYCENTRIC_DISTANCE | GAIA_TEFF;
	p_model->celestial_body_size = gaiaGetBodySize(p_model->celestial_body_flags);
	p_model->available_video_memory = available_gpu_heap / 2;

	return 1;
}

uint8_t gaiaReadSources(GaiaModelDescriptorInfo descriptor_info, GaiaUniverseModelMemory* p_model) {
	gaiaError(p_model == NULL, "invalid universe model memory", return 0);

	p_model->p_celestial_bodies = calloc(1, p_model->available_video_memory);
	gaiaError(p_model->p_celestial_bodies == NULL, "invalid celestial bodies memory", return 0);

	printf("Available VRAM: %i\n", p_model->available_video_memory);
	puts("gaiaReadResources: loading universe model files...");
	
	for (uint32_t i = descriptor_info.source_start; i < p_model->resource_count; i++) {

		void*    p_src      = NULL;
		uint32_t bytes_read = 0;

		gaiaError(
			gaiaReadBinaryFileFromID("../../../gaia-bin/", i, p_model->celestial_body_flags, 0, 0, &bytes_read, &p_src) == 0,
			"failed reading source file",
			return 0;
		);

		if (p_model->used_gpu_heap + bytes_read >= p_model->available_video_memory) {
			gaiaFree(p_src);
			break;
		}

		memcpy(&((char*)p_model->p_celestial_bodies)[p_model->used_gpu_heap], p_src, bytes_read);
		p_model->used_gpu_heap += bytes_read;

		gaiaFree(p_src);
	}

	return 1;
}

uint8_t gaiaBuildPipeline(ShEngine* p_engine, GaiaUniverseModelMemory* p_model) {
	gaiaError(p_engine == NULL, "invalid engine memory", return 0);
	gaiaError(p_model == NULL, "invalid universe model memory", return 0);

	p_model->p_pipeline = &p_engine->p_materials[0].pipeline;
	p_model->p_fixed_states = &p_engine->p_materials[0].fixed_states;
	VkDevice device = p_engine->core.device;
	
	puts("gaiaBuildPipeline: buildings celestial body pipeline");
		
	{//PUSH CONSTANT
		shSetPushConstants(VK_SHADER_STAGE_VERTEX_BIT, 0, 128, &p_model->p_pipeline->push_constant_range);
	}//PUSH CONSTANT

	{//DESCRIPTOR SET AND BUFFER
		shPipelineCreateDescriptorBuffer(device, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, 0, p_model->used_gpu_heap, p_model->p_pipeline);
		shPipelineAllocateDescriptorBufferMemory(device, p_engine->core.physical_device, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 0, p_model->p_pipeline);
		shPipelineBindDescriptorBufferMemory(device, 0, 0, p_model->p_pipeline);

		shPipelineDescriptorSetLayout(device, 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_SHADER_STAGE_VERTEX_BIT, p_model->p_pipeline);
		shPipelineCreateDescriptorPool(device, 0, p_model->p_pipeline);
		shPipelineAllocateDescriptorSet(device, 0, p_model->p_pipeline);


		shPipelineCreateDescriptorBuffer(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 1, 16, p_model->p_pipeline);
		shPipelineAllocateDescriptorBufferMemory(device, p_engine->core.physical_device, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 1, p_model->p_pipeline);
		shPipelineBindDescriptorBufferMemory(device, 1, 0, p_model->p_pipeline);

		shPipelineDescriptorSetLayout(device, 1, 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT, p_model->p_pipeline);
		shPipelineCreateDescriptorPool(device, 1, p_model->p_pipeline);
		shPipelineAllocateDescriptorSet(device, 1, p_model->p_pipeline);
	}//DESCRIPTOR SET AND BUFFER
	

	{//FIXED STATES
		shSetFixedStates(device, p_engine->core.surface.width, p_engine->core.surface.height, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_POLYGON_MODE_FILL, p_model->p_fixed_states);
	}//FIXED STATES

	{//SHADER STAGES
		char path[256];
		shMakeAssetsPath("/shaders/bin/celestialBody.vert.spv", path);
		uint32_t src_size = 0;
		char* src = (char*)shReadBinary(path, &src_size);
		shPipelineCreateShaderModule(device, src_size, src, p_model->p_pipeline);
		shPipelineCreateShaderStage(device, VK_SHADER_STAGE_VERTEX_BIT, p_model->p_pipeline);
		free(src);
		shMakeAssetsPath("/shaders/bin/celestialBody.frag.spv", path);
		src = (char*)shReadBinary(path, &src_size);
		shPipelineCreateShaderModule(device, src_size, src, p_model->p_pipeline);
		shPipelineCreateShaderStage(device, VK_SHADER_STAGE_FRAGMENT_BIT, p_model->p_pipeline);
		free(src);
	}//SHADER STAGES

	{//GRAPHICS PIPELINE
		shSetupGraphicsPipeline(device, p_engine->core.render_pass, *p_model->p_fixed_states, p_model->p_pipeline);
	}//GRAPHICS PIPELINE

	return 1;
}

uint8_t gaiaWriteMemory(ShEngine* p_engine, GaiaUniverseModelMemory* p_model) {
	
	puts("gaiaWriteMemory: writing memory");

	VkDevice device = p_engine->core.device;
	VkPhysicalDevice physical_device = p_engine->core.physical_device;
	VkCommandBuffer* p_cmd_buffer = &p_engine->core.p_graphics_commands[0].cmd_buffer;
	VkFence* p_fence = &p_engine->core.p_graphics_commands[0].fence;

	VkBuffer staging_buffer = NULL;
	VkDeviceMemory staging_buffer_memory = NULL;
	shCreateBuffer(device, p_model->used_gpu_heap, VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, &staging_buffer);
	shAllocateMemory(device, physical_device, staging_buffer, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &staging_buffer_memory);
	shWriteMemory(device, staging_buffer_memory, 0, p_model->used_gpu_heap, p_model->p_celestial_bodies);
	shBindMemory(device, staging_buffer, 0, staging_buffer_memory);

	VkBuffer model_buffer = p_model->p_pipeline->descriptor_buffers[0];
	VkDeviceMemory model_buffer_memory = p_model->p_pipeline->descriptor_buffers_memory[0];
	
	{
		shWaitForFences(device, 1, p_fence);
		shResetFence(device, p_fence);

		shBeginCommandBuffer(*p_cmd_buffer);
		shCopyBuffer(*p_cmd_buffer, staging_buffer, 0, 0, p_model->used_gpu_heap, model_buffer);
		shEndCommandBuffer(*p_cmd_buffer);

		shQueueSubmit(1, p_cmd_buffer, p_engine->core.graphics_queue.queue, *p_fence);

		shWaitForFences(device, 1, p_fence);
	}
	
	shClearBufferMemory(device, staging_buffer, staging_buffer_memory);

	return 1;
}



#ifdef __cplusplus
}
#endif//__cplusplus