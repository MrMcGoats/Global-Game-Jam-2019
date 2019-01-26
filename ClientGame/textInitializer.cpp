// Not sure where this goes but this includes code that registers the fonts and also creates a number of text based actors.


// Register the fonts
RegisterFont("Resources/Fonts/PermanentMarker-Regular.ttf", 20, "Marker20");
RegisterFont("Resources/Fonts/Quantico-Bold", 12, "Score12");

//Title Card
TextActor *t = new TextActor("Title", "<Insert Name of Game Here>", TXT_Center);
theWorld.Add(t);

//Credits
TextActor *x = new TextActor("Credits", "Programmer", <position here>);
theWorld.Add(x);

//Player Scores, position not defined.
TextActor *a = new TextActor("P1", "Player 1 Score: ", <Position goes here>);
theWorld.Add(a);

TextActor *b = new TextActor("P2", "Player 2 Score: ", <Position goes here>);
theWorld.Add(b);

//Number Score, will need to be changed on the fly!
TextActor *c = new TextActor("P1S", <Player1 Score Variable, as String>, <Position goes here>);
theWorld.Add(c);

TextActor *d = new TextActor("P2S", <Player2 Score Variable, as String>, <Position goes here>);
theWorld.Add(d);