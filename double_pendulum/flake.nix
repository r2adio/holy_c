{
  description = "double-pendulum";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      supportedSystems = [ "aarch64-darwin" "x86_64-darwin" ];
      forAllSystems = f: nixpkgs.lib.genAttrs supportedSystems (system: f (import nixpkgs { inherit system; }));
    in
    {
      devShells = forAllSystems (pkgs: {
        default = pkgs.mkShell {
          name = "double_pendulum";
          nativeBuildInputs = with pkgs; [ gcc gnumake pkg-config bear ];
          buildInputs = with pkgs; [ raylib ];
          shellHook = '' exec ${pkgs.zsh}/bin/zsh '';
        };
      });
    };
}
