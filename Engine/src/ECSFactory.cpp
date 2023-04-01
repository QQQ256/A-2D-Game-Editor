#include "ECSFactory.hpp"

void ECSFactory::Init(){
    Debug::PrintMessage("ECSInit");
    this->InitComponents();

    this->InitSybSystems();

    this->InitEntities();
}

void ECSFactory::InitComponents(){
    // ///////////////////////////////////////////
    // //         set up component here         //
    // ///////////////////////////////////////////
    coordinator.RegisterComponent<Transform>();
    coordinator.RegisterComponent<Player>();
    coordinator.RegisterComponent<Sprite>();
    coordinator.RegisterComponent<Tilemap>();
    coordinator.RegisterComponent<Renderer>();
    coordinator.RegisterComponent<Enemy>();
    coordinator.RegisterComponent<InPut>();
    coordinator.RegisterComponent<Editor>();
    coordinator.RegisterComponent<UIButton>();
    coordinator.RegisterComponent<Camera>();
}

void ECSFactory::InitSybSystems(){
    // ///////////////////////////////////////////
    // //         set up System here            //
    // ///////////////////////////////////////////
    coordinator.m_SDLGraphicsSystem = coordinator.RegisterSystem<SDLGraphicsSystem>();
    {
        coordinator.m_SDLGraphicsSystem->SetSDLWindow(WINDOW_WIDTH, WINDOW_HIEGHT);
    }
    coordinator.m_SDLGraphicsSystem->Init();




    coordinator.m_SpriteSystem = coordinator.RegisterSystem<SpriteSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentTypeUniqueIndex<Sprite>());

        coordinator.SetSignature<SpriteSystem>(signature);
    }
    coordinator.m_SpriteSystem->Init();




    coordinator.m_PlayerControllerSystem = coordinator.RegisterSystem<PlayerControllerSystem>();
    {
        Signature signature;

        // set a subsystem's unique Signature
        signature.set(coordinator.GetComponentTypeUniqueIndex<Transform>());
        signature.set(coordinator.GetComponentTypeUniqueIndex<Player>());

        // here, set a unique signature based on the component attached
        coordinator.SetSignature<PlayerControllerSystem>(signature);
    }
    coordinator.m_PlayerControllerSystem->Init();




    coordinator.m_TilemapSystem = coordinator.RegisterSystem<TilemapSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentTypeUniqueIndex<Tilemap>());

        coordinator.SetSignature<TilemapSystem>(signature);
    }
    coordinator.m_TilemapSystem->Init();




    coordinator.m_RenderSystem = coordinator.RegisterSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentTypeUniqueIndex<Renderer>());

        coordinator.SetSignature<RenderSystem>(signature);
    }
    coordinator.m_RenderSystem->Init();


    coordinator.m_InputSystem = coordinator.RegisterSystem<InputSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentTypeUniqueIndex<InPut>());

        coordinator.SetSignature<InputSystem>(signature);
    }
    coordinator.m_InputSystem->Init();

    
    coordinator.m_LevelEditorSystem = coordinator.RegisterSystem<LevelEditorSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentTypeUniqueIndex<Editor>());

        coordinator.SetSignature<LevelEditorSystem>(signature);
    }
    coordinator.m_LevelEditorSystem->Init();

    coordinator.m_UISystem = coordinator.RegisterSystem<UISystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentTypeUniqueIndex<UIButton>());

        coordinator.SetSignature<UISystem>(signature);
    }
    coordinator.m_UISystem->Init();

    coordinator.m_CameraSystem = coordinator.RegisterSystem<CameraSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentTypeUniqueIndex<Camera>());

        coordinator.SetSignature<CameraSystem>(signature);
    }
    coordinator.m_CameraSystem->Init();

}

void ECSFactory::InitEntities(){
    // ///////////////////////////////////////////
    // //         set up entity here           //
    // ///////////////////////////////////////////
    CreatePlayerFromJSON();

    CreateTilemapFromJSON();

    CreateEnemyFromJSON();

    CreateEditorUI();

    CreateCamera();
    
}

void ECSFactory::CreatePlayerFromJSON()
{
    Entity player;
    if (FileReader::GetInstance().LoadJSONFile(JSON_CONFIG)){
        player = coordinator.CreateEntity();

        auto config = FileReader::GetInstance().GetConfig();
        auto playerConfig = config["Player"];

        coordinator.AddComponent(player, InPut{});
        coordinator.AddComponent(player, Player{
            playerConfig["speed"]
        });
        coordinator.AddComponent(player, Transform{
            Vec2D(0, 0)
        });
        coordinator.AddComponent(player, Sprite{
            coordinator.m_SpriteSystem->CreateSprite(
                playerConfig["filePath"], 
                coordinator.m_SDLGraphicsSystem->GetSDLRenderer(),
                playerConfig["sizeX"], 
                playerConfig["sizeY"], 
                playerConfig["posX"], 
                playerConfig["posY"], 
                playerConfig["frame"]
            )
        });
        coordinator.AddComponent(player, Renderer{RENDER_ORDER::OBJECT});
        coordinator.m_RenderSystem->AddEntity(player);
    }

    // this->AddEntity(ENTITY_TYPE::ENEMY);
}

void ECSFactory::CreateTilemapFromJSON()
{
    Entity tilemap;
    vector<int> tempList;

    if (FileReader::GetInstance().LoadTilemapText(TILEMAP_TXT)
        && FileReader::GetInstance().LoadJSONFile(JSON_CONFIG))
    {
        tilemap = coordinator.CreateEntity();
        
        auto config = FileReader::GetInstance().GetConfig();
        auto tilemapConfig = config["Tilemap"];

        auto tilemapData = FileReader::GetInstance().GetTilemapData();
        
        coordinator.AddComponent(tilemap, Tilemap{
            coordinator.m_TilemapSystem->CreateTileMap(
                tilemapConfig["filePath"],
                tilemapConfig["rows"],
                tilemapConfig["cols"],
                tilemapConfig["tileWidth"],
                tilemapConfig["tileHeight"],
                tilemapConfig["mapX"],
                tilemapConfig["mapY"],
                tilemapConfig["scaleFactor"],
                tilemapData
            )
        });

        coordinator.AddComponent(tilemap, InPut{});

        coordinator.AddComponent(tilemap, Renderer{RENDER_ORDER::BACKGROUND});
        coordinator.m_RenderSystem->AddEntity(tilemap);
    }
}

void ECSFactory::AddEntity(ENTITY_TYPE entity_type)
{
    Enemy enemy{100, 100};
    switch (entity_type)
    {
    case ENTITY_TYPE::ENEMY:
        // this->AddEnemyToJSON(enemy);
        break;
    
    default:
        break;
    }
}

// TODO: 读取多个，并生成出来；看懂tilemap，试试能不能做出生成tilemap;
void ECSFactory::AddEnemyToJSON(Enemy enemyData)
{
    // if (FileReader::GetInstance().LoadJSONFile(JSON_CONFIG))
    // {
    //     // create entity
    //     Entity enemy;
    //     enemy = coordinator.CreateEntity();

    //     // create a new enemy
    //     json newEnemyConfig = {
    //         {"health", enemyData.health},
    //         {"speed" , enemyData.speed}
    //     };

    //     // get config object
    //     auto currentConfig = FileReader::GetInstance().GetConfig();
    //     currentConfig["Enemy"].push_back(newEnemyConfig);

    //     // add entities to the enemy
    //     coordinator.AddComponent(enemy, enemyData);
    //     // TODO: Create sprite here
    //     coordinator.AddComponent(enemy, Sprite{
    //         coordinator.m_SpriteSystem->CreateSprite(
    //             "./images/sprite.bmp",
    //             coordinator.m_SDLGraphicsSystem->GetSDLRenderer(),
    //             10,
    //             10,
    //             6
    //         )
    //     });
    //     coordinator.AddComponent(enemy, Renderer{RENDER_ORDER::OBJECT});
    //     coordinator.m_RenderSystem->AddEntity(enemy);

    //     FileReader::GetInstance().SaveJSONFile(currentConfig, JSON_CONFIG);

    // }
}

void ECSFactory::CreateEditorUI()
{
    bool isUIFileExist = FileReader::GetInstance().LoadJSONFile(UI_JSON_CONFG);

    if(!isUIFileExist){
        cout << "Cannot open: " << UI_JSON_CONFG << endl;
        return;
    }
    else{
        auto config = FileReader::GetInstance().GetConfig();
        auto buttonConfig = config["Buttons"];

        Entity btn_AddTile;
        Entity btn_RemoveTile;

        CreateButton(btn_AddTile, "Btn_AddTile", buttonConfig);
        CreateButton(btn_AddTile, "Btn_RemoveTile", buttonConfig);
    }
}

void ECSFactory::CreateButton(Entity entity, const string& btnName, const json& buttonConfig)
{
    entity = coordinator.CreateEntity();

    coordinator.AddComponent(entity, UIButton{
        
    });

    coordinator.AddComponent(entity, Sprite{
        coordinator.m_SpriteSystem->CreateSprite(
                buttonConfig[btnName]["filePath"],
                coordinator.m_SDLGraphicsSystem->GetSDLRenderer(),
                buttonConfig[btnName]["size"]["w"],
                buttonConfig[btnName]["size"]["h"],
                buttonConfig[btnName]["position"]["x"], 
                buttonConfig[btnName]["position"]["y"], 
                0
            )
    });
    coordinator.AddComponent(entity, Editor{
        
    });

    coordinator.AddComponent(entity, Renderer{RENDER_ORDER::UI});
    coordinator.m_RenderSystem->AddEntity(entity);
}

void ECSFactory::CreateEnemyFromJSON()
{
    if (FileReader::GetInstance().LoadJSONFile(JSON_CONFIG))
    {
        // get config object
        auto config = FileReader::GetInstance().GetConfig();
        auto enemyConfig = config["Enemy"];

        for(int i = 0; i < enemyConfig.size(); i++){
            // create entity
            Entity enemy;
            enemy = coordinator.CreateEntity();

            // 添加Enemy组件
            coordinator.AddComponent(enemy, Enemy{
                enemyConfig[i]["health"],
                enemyConfig[i]["speed"]
            });

            // 添加Sprite组件
            coordinator.AddComponent(enemy, Sprite{
                // 使用你的创建Sprite的方法
                coordinator.m_SpriteSystem->CreateSprite(
                    enemyConfig[i]["filePath"],
                    coordinator.m_SDLGraphicsSystem->GetSDLRenderer(),
                    enemyConfig[i]["sizeX"],
                    enemyConfig[i]["sizeY"],
                    enemyConfig[i]["posX"], 
                    enemyConfig[i]["posY"], 
                    enemyConfig[i]["frame"]
                )
            });
            
            // 添加Input组件，因为鼠标要检测是否碰到了enemy，需要在inputSystem中用到这个entity
            coordinator.AddComponent(enemy, InPut{});

            coordinator.AddComponent(enemy, Renderer{RENDER_ORDER::OBJECT});
            coordinator.m_RenderSystem->AddEntity(enemy);
        }
    }
}

void ECSFactory::CreateCamera()
{
    Entity camera;
    camera = coordinator.CreateEntity();

    coordinator.AddComponent(camera, Camera{
        coordinator.m_CameraSystem->CreateCamera(
            0,
            0,
            1920,
            1080,
            1920,
            1080
        )
    });
}
