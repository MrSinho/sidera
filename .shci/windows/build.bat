> .shci/windows/build-output.txt (
    cd externals/shengine
    python export-application.py name=gaia-universe-model target=EXECUTABLE path=../../gaia-universe-model
    cd ../../gaia-universe-model/windows/build
    cmake --build .
)
