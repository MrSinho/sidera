function BUILD {
	mkdir linux-build
	cd linux-build
	cmake ..
	cmake --build .
}

BUILD > .shci/linux/build-output.txt
