level.player_position(0.5, 1.5);
level.player_rotation(-Math.PI / 2);

level.register_wall(
  new Wall(0, 0, 1, 0)
  .color("#355c32")
  .checkerboard()
);

level.register_wall(
  new Wall(0.25, 0.01, 0.75, 0.01)
  .image("resources/bone.png", 0.5, 0.5)
);

level.register_wall(
  new Wall(0, 0, 0, 1)
  .color("#1f6e78")
  .bounce()
);
