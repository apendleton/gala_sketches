(function() {
    var qs = parseQuery(window.location.search);
    let vid = qs.vid ? qs.vid + ".json" : "blue.json"
    let ifr = qs.ifr ? parseInt(qs.ifr, 10) : 100;
    fetch(vid).then(function(response) {
        return response.json();
    }).then(function(frames) {
        setAllLow();

        var current = 0;
        setInterval(function() {
            let frame = frames[current];
            for (var row = 0; row < 24; row++) {
                for (var col = 0; col < 24; col++) {
                    setRingGlobalQ(row, col, frame[col][row]);
                }
            }
            current = (current + 1) % frames.length;
        }, ifr);
    })
})();