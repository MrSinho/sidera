function BUILD {
	cd externals/shengine
    python3.9 export-application.py name=gaia-universe-model target=EXECUTABLE path=../../gaia-universe-model
    cd ../../gaia-universe-model/linux/build
    cmake --build .
}

BUILD > .shci/linux/build-output.txt
