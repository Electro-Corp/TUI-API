{ pkgs }: {
	deps = [
		pkgs.xterm
  pkgs.nano
  pkgs.nasm
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}