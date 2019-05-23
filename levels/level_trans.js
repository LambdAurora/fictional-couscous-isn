level.player_position(0, -1)
  .background("#636363")
  .ground("#575757");

level.register_wall(
  new Wall(-0.5, 0, 0.5, 0)
  .image("resources/carton-detoure-s.png", 1, 1)
);

level.register_wall(
  new Wall(0, -0.33, 0.5, -0.33)
  .ghost()
  .transparent(0.3)
  .color("#7fd295")
);
