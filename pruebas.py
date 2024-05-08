from manim import *


class Grafos(Scene):
    def construct(self):
        vertices = [1]
        edges = [(1, 1)]
        numV = len(vertices)

        g = Graph(vertices, edges, layout="circular", layout_scale=3, labels=True)
        self.add(g)
