(function() {
    setAllLow();

    var levels = new Array(12);
    var active = new Array(12);
    var activeCount = 12;
    for (var i = 0; i < 12; i++) {
        levels[i] = 0;
        active[i] = i;
    }

    var currentCol = null;
    var currentHeight = -1;
    var target = -1;
    var pick;
    var direction = 1;
    var x = setInterval(function() {
        if (currentHeight == target) {
            if (currentCol != -1) {
                levels[currentCol] += 1;
                if (levels[currentCol] == 12) {
                    var tmp = active[pick];
                    active[pick] = active[activeCount - 1];
                    active[activeCount - 1] = tmp;
                    activeCount--;

                    if (activeCount == 0) {
                        activeCount = 12;
                        direction = (direction == 1 ? -1 : 1);
                        for (var i = 0; i < 12; i++) {
                            levels[i] = 0;
                        }
                    }
                }
            }


            pick = random(activeCount);
            currentCol = active[pick];

            if (direction == 1) {
                currentHeight = 0;
                target = 12 - levels[currentCol];
            } else {
                currentHeight = (12 - levels[currentCol]);
                target = 13;
            }
        }

        if (currentHeight < 12) setLight(currentHeight, currentCol, HIGH);
        if (currentHeight > 0) setLight(currentHeight - 1, currentCol, LOW);
        currentHeight += 1;
    }, 25);
})();