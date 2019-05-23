level.player_position(-1, 0.5)
  .scale(0.7)
  .background("#d1d5c9");

level.register_wall(
  new Wall(0, 0, 1, 0)
  .color("#53bebb")
  .gradient("#419fc7")
  .bounce()
);

level.register_wall(
  new Wall(0, 0, 0, 1)
  .color("#71be76")
  .checkerboard()
);

level.register_wall(
  new Wall(0, 1, -0.5, 1)
  .color("#e4d654")
  .gradient("#f48289")
);

level.register_wall(
  new Wall(-2, -0.5, -2, 0.5)
  .transparent(0.5)
  .color("#7a3a90")
);

level.register_wall(
  new Wall(-1.5, -0.5, -1, -0.5)
  .image("resources/flower.png", 0.5, 0.5)
  .ghost()
);

level.register_wall(
  new Wall(2, 2, 2, -2.5)
  .color("#b4bf7a")
);

level.register_wall(
  new Wall(-2.5, 2, -2.5, -2.5)
  .color("#7d7d7d")
  .bounce()
);

let wall_teleport_1 = new Wall(2, 2, -2.5, 2);
let wall_teleport_2 = new Wall(2, -2.5, -2.5, -2.5);

wall_teleport_1.teleport(wall_teleport_2);
wall_teleport_2.teleport(wall_teleport_1);

level.register_wall(wall_teleport_1);
level.register_wall(wall_teleport_2);
