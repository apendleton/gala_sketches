var setLight, setLevel, setAllHigh, setAllLow;
var LOW = 0, HIGH = 1;

(function() {
    setLight = function(row, col, state) {
        var light = document.querySelectorAll('.row-' + row + ' .col-' + col);
        light[0].style.backgroundColor = state ? '#cccccc': '#444444';
    }

    var setAll = function(state) {
        var lights = document.querySelectorAll('td');
        for (let light of lights) {
            light.style.backgroundColor = state ? '#cccccc': '#444444';
        }
    }

    setAllLow = function() { setAll(LOW); }
    setAllHigh = function() { setAll(HIGH); }

    random = function(min, max) {
        if (typeof max == 'undefined') {
            max = min;
            min = 0;
        }

        return Math.floor(Math.random() * (max - min)) + min;
    }
})();