import webview, time, os, math

from threading import Thread

def run(func):
    def thread():
        time.sleep(1)

        index = os.path.join(os.path.abspath(os.path.dirname(__file__)), "index_led.html")
        webview.load_html(open(index).read())
        time.sleep(1)

        func()

    t = Thread(target=thread)
    t.start()

    webview.create_window("Test", "", width=700, height=700)

def getColor(triple):
    return "rgb({})".format(",".join(map(str, triple)))

def setAllRings(color):
    webview.evaluate_js("""
    (function() {{
        var lights = document.querySelectorAll('circle');
        for (let light of lights) {{
            light.setAttributeNS(null, 'fill', '{color}');
        }}
    }})()
    """.format(color=getColor(color)))

def setAllRingsLow():
    setAllRings((0,0,0))

def setAllRingsHigh():
    setAllRings((255,255,255))

def setRing(row, col, color):
    webview.evaluate_js("""
    (function() {{
        var lights = document.querySelectorAll('.row-{row}.col-{col} circle');
        for (let light of lights) {{
            light.setAttributeNS(null, 'fill', '{color}');
        }}
    }})()
    """.format(row=row, col=col, color=getColor(color)))

def setRingL(row, col, l, color):
    webview.evaluate_js("""
    (function() {{
        var lights = document.querySelectorAll('.row-{row}.col-{col} circle.l-{l}');
        for (let light of lights) {{
            light.setAttributeNS(null, 'fill', '{color}');
        }}
    }})()
    """.format(row=row, col=col, l=l, color=getColor(color)))

def setRingQ(row, col, q, color):
    webview.evaluate_js("""
    (function() {{
        var lights = document.querySelectorAll('.row-{row}.col-{col} circle.q-{q}');
        for (let light of lights) {{
            light.setAttributeNS(null, 'fill', '{color}');
        }}
    }})()
    """.format(row=row, col=col, q=q, color=getColor(color)))

qs = [[3,0],[1,2]]
def setRingGlobalQ(rowq, colq, color):
    rq = rowq % 2
    row = int(math.floor(rowq/2.0))
    cq = colq % 2
    col = int(math.floor(colq/2.0))
    q = qs[rq][cq]

    setRingQ(row, col, q, color)

def render():
    pass
