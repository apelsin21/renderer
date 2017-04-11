 with import <nixpkgs> {}; {
	sdlEnv = stdenv.mkDerivation {
		name = "renderer";
		buildInputs = [
      stdenv
      cmake
      SDL2
      freeimage
      freetype
      enet
      mesa_glu
      epoxy
      pkgconfig
      valgrind
      gdb
      apitrace
    ];
	};
}
