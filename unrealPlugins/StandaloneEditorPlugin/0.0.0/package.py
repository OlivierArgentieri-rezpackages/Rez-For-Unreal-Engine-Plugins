name = "StandaloneEditorPlugin"
version = "4.26.2"

requires = [
    "unreal"
]

def commands():
    env.UNREAL_PLUGIN_PATH.append(r'{this.root}/StandaloneEditorPlugin')  # noqa
