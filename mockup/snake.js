(function() {
    setAllLow();

    var LENGTH = 6;
    var HEAD = LENGTH - 1;
    var TAIL = 0;

    var bodyRows = new Array(LENGTH);
    var bodyCols = new Array(LENGTH);

    for (var i = 0; i < LENGTH; i++) {
        bodyCols[i] = i;
        bodyRows[i] = 0;
        setLight(0, i, HIGH);
    }

    var nextRows = new Array(4);
    var nextCols = new Array(4);
    var count = 0;
    setInterval(function() {
        count = 0;

        if (bodyRows[HEAD] > 0 && bodyRows[HEAD - 1] != bodyRows[HEAD] - 1) {
            nextRows[count] = bodyRows[HEAD] - 1;
            nextCols[count] = bodyCols[HEAD];
            count++;
        }

        if (bodyRows[HEAD] < 11 && bodyRows[HEAD - 1] != bodyRows[HEAD] + 1) {
            nextRows[count] = bodyRows[HEAD] + 1;
            nextCols[count] = bodyCols[HEAD];
            count++;
        }

        if (bodyCols[HEAD] > 0 && bodyCols[HEAD - 1] != bodyCols[HEAD] - 1) {
            nextRows[count] = bodyRows[HEAD];
            nextCols[count] = bodyCols[HEAD] - 1;
            count++;
        }

        if (bodyCols[HEAD] < 11 && bodyCols[HEAD - 1] != bodyCols[HEAD] + 1) {
            nextRows[count] = bodyRows[HEAD];
            nextCols[count] = bodyCols[HEAD] + 1;
            count++;
        }

        var pick = random(count);
        var tailRow = bodyRows[TAIL];
        var tailCol = bodyCols[TAIL];
        for (let i = 0; i < LENGTH - 1; i++) {
            bodyRows[i] = bodyRows[i + 1];
            bodyCols[i] = bodyCols[i + 1];
        }
        bodyRows[HEAD] = nextRows[pick];
        bodyCols[HEAD] = nextCols[pick];
        setLight(bodyRows[HEAD], bodyCols[HEAD], HIGH);

        var doubleTail = false
        for (var i = 0; i < LENGTH; i++) {
            doubleTail = doubleTail || (tailRow == bodyRows[i] && tailCol == bodyCols[i]);
        }
        if (!doubleTail) {
            setLight(tailRow, tailCol, LOW);
        }
    }, 200);
})();