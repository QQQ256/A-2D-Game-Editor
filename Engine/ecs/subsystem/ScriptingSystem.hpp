#pragma once

using namespace std;

class ScriptingSystem : public ISystem {
public:
	void Init() override;

	void Update() override;

    void Shutdown();

private:
    void Execute(const char *);
};
