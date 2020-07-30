indexInputFileName="index.html"
indexOutputFileName="build/index.h"

if [[ ! -d build ]]; then
    mkdir build
fi

rm -rf ${indexOutputFileName}
echo 'const char html_index[] PROGMEM = R"=====(' >${indexOutputFileName}
cat ${indexInputFileName} >>${indexOutputFileName}
echo '\n)=====";' >>${indexOutputFileName}
echo 'Done'
