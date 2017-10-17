(function() {
    setAllLow();

    var current = 0;

    setInterval(function() {
        if (current < 6) {
            for (var i = 0; i < 12; i++) {
                setLight(current * 2, i, HIGH);
            }
        } else if (current >= 60) {
            current = 0;
            setAllLow();
        }

        current += 1;
    }, 2000);
})();