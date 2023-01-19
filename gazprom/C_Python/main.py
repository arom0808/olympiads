input_params = [{"x": 4032, "y": 2970}, {"x": 3032, "y": 2954}, {"x": 578, "y": 1970}, {"x": 3132, "y": 2854}]


def CalmWinter(params):
    return min(2200, params["x"]) * 35 + min(3500, params["y"]) * 58 - params["x"] * 19 - params["y"] * 25


def StrongWinter(params):
    return min(3800, params["x"]) * 35 + min(2450, params["y"]) * 58 - params["x"] * 19 - params["y"] * 25


for i in range(len(input_params)):
    print(str(i + 1) + ":")
    calm, strong = CalmWinter(input_params[i]), StrongWinter(input_params[i])
    print("min(" + str(calm) + ", " + str(strong) + ") = " + str(min(calm, strong)))
    print()
