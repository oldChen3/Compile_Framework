How to build and clean project：
  1.to build project, to run: ./build.sh build
  2.to clean up all unnessary file to run: ./build.sh clean_all

How to add your app code:
  1.put your project in Apps/, just like Apps/TestApp
  2.create a scripts in scripts/ to compile you project, just like scripts/TestApp/TestApp-build.sh
  3.call your compile script in build.sh, just like build_testApp(){... ./${TestApp-build.sh} build ...}


