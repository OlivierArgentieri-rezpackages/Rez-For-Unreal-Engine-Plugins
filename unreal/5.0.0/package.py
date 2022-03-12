name = "unreal"
version = "5.0.0"

tools = [
    "UnrealEditor-Cmd",
    "UnrealEditor",
    "start_engine"
]


def commands():
    env.PATH.append(f"{root}")
    env.PATH.append(r'F:\UnrealEditor\UE_5.0EA\Engine\Binaries\Win64')  # noqa
