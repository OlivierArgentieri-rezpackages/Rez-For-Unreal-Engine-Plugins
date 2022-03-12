name = "unreal"
version = "4.26.2"

tools = [
    "UnrealEditor-Cmd",
    "UnrealEditor",
]


def commands():
    env.PATH.append(r'F:\UnrealEditor\UE_5.0EA\Engine\Binaries\Win64')  # noqa
