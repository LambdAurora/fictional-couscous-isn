level.player_position(0.5, 0.75);
level.player_rotation(-Math.PI / 6);

level.register_wall(
  new Wall(0, 0, 1.5, 0)
  .color("#355c32")
  .checkerboard()
);

level.register_wall(
  new Wall(0.25, 0.01, 0.75, 0.01)
  .image("resources/bone.png", 0.5, 0.5)
);

level.register_wall(
  new Wall(0, 1, 1.5, 1)
  .color("#325c57")
  .checkerboard()
);

level.register_wall(
  new Wall(0.75, 0.99, 1.25, 0.99)
  .image("resources/flower.png", 0.5, 0.5)
);

let wall_a = new Wall(0, 0, 0, 1)
    .color("#1f6e78");

let wall_b = new Wall(1.5, 0, 1.5, 1)
    .color("#d07927");

wall_a.teleport(wall_b);
wall_b.teleport(wall_a);

level.register_wall(wall_a);
level.register_wall(wall_b);
