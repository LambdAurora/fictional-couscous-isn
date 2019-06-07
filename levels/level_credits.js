level.player_position(1.5, -5)
  .player_rotation(Math.PI * .4)
  .ground("#544357")
  .background("#b4b7d4");

level.register_wall(
  new Wall(0, 0, 0, 3)
  .color("#a1849e")
  .checkerboard()
);

level.register_wall(
  new Wall(0, 3, 3, 3)
  .color("#b4b69f")
  .checkerboard()
);

level.register_wall(
  new Wall(0, 0, 1, 0)
  .color("#555088")
  .gradient("#b8b8b8")
);

level.register_wall(
  new Wall(2, 0, 3, 0)
  .color("#b8b8b8")
  .gradient("#555088")
);

level.register_wall(
  new Wall(3, 0, 3, 1)
  .color("#d66fa7")
  .gradient("#b8b8b8")
);

level.register_wall(
  new Wall(3, 2, 3, 3)
  .color("#b8b8b8")
  .gradient("#d66fa7")
);

let wall_a = new Wall(1, 0, 2, 0);
let wall_b = new Wall(3, 2, 3, 1);

wall_a.teleport(wall_b);
wall_b.teleport(wall_a);

level.register_wall(wall_a);
level.register_wall(wall_b);

level.register_wall(
  new Wall(4, 3, 7, 3)
  .image("resources/face.png", 1, 1)
  .ghost()
);

level.register_room(
  new Room(5, 1, 1, 1)
  .color("#a37a7f")
  .wall(true)
);

level.register_room(
  new Room(1, -2, 1, 1)
  .color("#8492a4")
  .wall(true)
);

/*

*---* ???
|   |
|   >  #
|   |
*-^-*
// 0,0

  #
*/
