void BotCoordinatesHandler(int coords);
void GameRender(int plr[12][12], bool ShowShip);
void DebugRender(int plr[12][12]);
int ShipPlacer(int plr[12][12], char pos[3], int shipsize);
int botship(int plr[12][12], int shipsize, int ships);
int ShipManager(int plr[12][12]);
int Attack(int plr[12][12], bool isBot);
void Game(int plr1[12][12], int plr2[12][12], bool isBot);