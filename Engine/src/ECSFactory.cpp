#include "ECSFactory.hpp"

ECSFactory::ECSFactory() : m_IsInitEditorSystem(false), m_IsInitComponents(false), m_IsInitCommonEntity(false), m_IsConfigFileExist(false)
{
    m_IsUIConfigFileExist = FileReader::GetInstance().LoadJSONFile(UI_CONFIG);
    m_IsConfigFileExist = FileReader::GetInstance().LoadJSONFile(COMPONENT_CONFIG);

    if(m_IsUIConfigFileExist)
    {
        m_Config = FileReader::GetInstance().GetConfig(UI_CONFIG);
        m_ImageConfig = m_Config["Images"];
        m_ButtonConfig = m_Config["Buttons"];
    }

    if(m_IsConfigFileExist){
        m_Config = FileReader::GetInstance().GetConfig(COMPONENT_CONFIG);
        m_CameraConfig = m_Config["Camera"];
    }
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
    coordinator.RegisterComponent<UIComponent>();
    coordinator.RegisterComponent<Camera>();
    coordinator.RegisterComponent<Name>();
    coordinator.RegisterComponent<Script>();
    coordinator.RegisterComponent<PhysicsBody>();
}

void ECSFactory::InitMenu()
{
    if (!this->m_IsInitComponents)
    {
        this->InitComponents();
        this->m_IsInitComponents = true;
    }

    RegisterMenuSystem();

    RegisterMenuEntity();
}

void ECSFactory::InitEditor()
{
    if (!this->m_IsInitEditorSystem)
    {

        // RegisterMenuSystem();
        RegisterCommonSystem();
        this->m_IsInitEditorSystem = true;

    }

    if (!this->m_IsInitCamera)
    {
        CreateCamera();
        this->m_IsInitCamera = true;
    }

    if(!this->m_IsInitCommonEntity){
        RegisterCommonEntity();
        this->m_IsInitCommonEntity = true;
    }
}

void ECSFactory::InitGame()
{
    if (!this->m_IsInitEditorSystem)
    {
        RegisterCommonSystem();

        this->m_IsInitEditorSystem = true;
    }

    if(!this->m_IsInitCommonEntity){
        RegisterCommonEntity();
        this->m_IsInitCommonEntity = true;
    }

    if (!this->m_IsInitCamera)
    {
        CreateCamera();
        this->m_IsInitCamera = true;
    }

    if(!this->m_IsInitGameSystem){

        coordinator.m_PhysicsManagerSystem = coordinator.RegisterSystem<PhysicsManagerSystem>();
        {
            Signature signature;
            signature.set(coordinator.GetComponentTypeUniqueIndex<PhysicsBody>());

            coordinator.SetSignature<PhysicsManagerSystem>(signature);
        }
        coordinator.m_PhysicsManagerSystem->Init();
        coordinator.m_PhysicsManagerSystem->SetGravity(0, 98);

        RegisterGameSystem();

        CreateTestEntityFromJSON();

        CreateTestEntitySecondFromJSON();

        CreatePlayerFromJSON();

        this->m_IsInitGameSystem = true;
    }
}

void ECSFactory::CreateTestEntityFromJSON()
{
    Entity testEntity;
    if (FileReader::GetInstance().LoadJSONFile(COMPONENT_CONFIG)){
        testEntity = coordinator.CreateEntity();

        auto config = FileReader::GetInstance().GetConfig(COMPONENT_CONFIG);
        auto testEntityConfig = config["TestEntity"];

        coordinator.AddComponent(testEntity, Script{
            testEntityConfig["scriptName"]
        });
        coordinator.AddComponent(testEntity, Name{
            testEntityConfig["name"]
        });
        coordinator.AddComponent(testEntity, Transform{
            Vec2D(testEntityConfig["transformX"], testEntityConfig["transformY"])
        });
        coordinator.AddComponent(testEntity, InPut{});
        coordinator.AddComponent(testEntity, Sprite{
            coordinator.m_SpriteSystem->CreateSprite(
                testEntityConfig["filePath"], 
                coordinator.m_SDLGraphicsSystem->GetSDLRenderer(),
                testEntityConfig["sizeX"], 
                testEntityConfig["sizeY"], 
                testEntityConfig["transformX"],
                testEntityConfig["transformY"],
                testEntityConfig["frame"]
            )
        });

        coordinator.AddComponent(testEntity, Renderer{RENDER_ORDER::OBJECT});
        coordinator.m_RenderSystem->AddEntity(testEntity);
    }
}

void ECSFactory::CreateTestEntitySecondFromJSON()
{
    Entity testEntity2;
    if (FileReader::GetInstance().LoadJSONFile(COMPONENT_CONFIG)){
        testEntity2 = coordinator.CreateEntity();

        auto config = FileReader::GetInstance().GetConfig(COMPONENT_CONFIG);
        auto testEntityConfig = config["TestEntity2"];

        coordinator.AddComponent(testEntity2, Script{
            testEntityConfig["scriptName"]
        });
        coordinator.AddComponent(testEntity2, Name{
            testEntityConfig["name"]
        });
        coordinator.AddComponent(testEntity2, Transform{
            Vec2D(testEntityConfig["transformX"], testEntityConfig["transformY"])
        });
        coordinator.AddComponent(testEntity2, InPut{});
        coordinator.AddComponent(testEntity2, Sprite{
            coordinator.m_SpriteSystem->CreateSprite(
                testEntityConfig["filePath"], 
                coordinator.m_SDLGraphicsSystem->GetSDLRenderer(),
                testEntityConfig["sizeX"], 
                testEntityConfig["sizeY"], 
                testEntityConfig["transformX"],
                testEntityConfig["transformY"],
                testEntityConfig["frame"]
            )
        });

        coordinator.AddComponent(testEntity2, Renderer{RENDER_ORDER::OBJECT});
        coordinator.m_RenderSystem->AddEntity(testEntity2);
    }
}

void ECSFactory::CreatePlayerFromJSON()
{
    Entity player;
    coordinator.m_PlayerEntity = player;
    if (FileReader::GetInstance().LoadJSONFile(COMPONENT_CONFIG)){
        player = coordinator.CreateEntity();

        auto config = FileReader::GetInstance().GetConfig(COMPONENT_CONFIG);
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
        // coordinator.AddComponent(player, Camera{});

        coordinator.AddComponent(player, Renderer{RENDER_ORDER::OBJECT});
        coordinator.m_RenderSystem->AddEntity(player);
    }

    Entity player1;
    player1 = coordinator.CreateEntity();
    // coordinator.AddComponent(player1, InPut{});
    coordinator.AddComponent(player1, Player{1});
    coordinator.AddComponent(player1, Transform{Vec2D(0,0)});
    coordinator.AddComponent(player1, Sprite{
        coordinator.m_SpriteSystem->CreateSprite(
            "./Resources/images/Mario.bmp",
            coordinator.m_SDLGraphicsSystem->GetSDLRenderer(),
            16,
            16,
            20,
            200,
            0
        )
    });
    coordinator.AddComponent(player1, Renderer{RENDER_ORDER::OBJECT});
    coordinator.m_RenderSystem->AddEntity(player1);
    coordinator.AddComponent(player1, PhysicsBody{
        coordinator.m_PhysicsManagerSystem->CreateB2Body(player1, DYNAMIC_SOLID),
        false
    });

    Entity player2;
    player2 = coordinator.CreateEntity();
    // coordinator.AddComponent(player2, InPut{});
    coordinator.AddComponent(player2, Player{1});
    coordinator.AddComponent(player2, Transform{Vec2D(0,0)});
    coordinator.AddComponent(player2, Sprite{
        coordinator.m_SpriteSystem->CreateSprite(
            "./Resources/images/Mario.bmp",
            coordinator.m_SDLGraphicsSystem->GetSDLRenderer(),
            16,
            16,
            20,
            600,
            0
        )
    });
    coordinator.AddComponent(player2, Renderer{RENDER_ORDER::OBJECT});
    coordinator.m_RenderSystem->AddEntity(player2);
    coordinator.AddComponent(player2, PhysicsBody{
        coordinator.m_PhysicsManagerSystem->CreateB2Body(player2, STATIC_SOLID),
        false
    });

    this->AddEntity(ENTITY_TYPE::ENEMY);
}

void ECSFactory::CreateTilemapFromJSON()
{
    Entity tilemap;
    vector<int> tempList;

    if (FileReader::GetInstance().LoadTilemapText(TILEMAP_TXT)
        && FileReader::GetInstance().LoadJSONFile(COMPONENT_CONFIG))
    {
        tilemap = coordinator.CreateEntity();
        
        auto config = FileReader::GetInstance().GetConfig(COMPONENT_CONFIG);
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
                tilemapData,
                tilemapConfig["gap"]
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
    // if (FileReader::GetInstance().LoadJSONFile(COMPONENT_CONFIG))
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

    //     FileReader::GetInstance().SaveJSONFile(currentConfig, COMPONENT_CONFIG);

    // }
}

void ECSFactory::CreateMenuUI()
{
    if (!this->m_IsUIConfigFileExist)
    {
        cout << "Cannot open: " << UI_CONFIG << endl;
        return;
    }
    else
    {
        Entity Img_Menu;
        Entity Btn_Menu_StartGame;

        // background
        CreateUIElement(Img_Menu, "Img_Menu", m_ImageConfig, GAME_STATE::MENU, UIType::MENU_IMAGE, RENDER_ORDER::_UI_);
        CreateUIElement(Btn_Menu_StartGame, "Btn_Menu_StartGame", m_ButtonConfig, GAME_STATE::MENU, UIType::MENU_IMAGE, RENDER_ORDER::_UI_);
    }
}

void ECSFactory::CreateEditorUI()
{
    if(!m_IsUIConfigFileExist){
        cout << "Cannot open: " << UI_CONFIG << endl;
        return;
    }
    else{

        Entity btn_AddTile;
        Entity btn_RemoveTile;

        // Create the button based on you want to render the button(ex. EDITOR, GAME, MENU)
        CreateUIElement(btn_AddTile, "Btn_AddTile", m_ButtonConfig, GAME_STATE::EDITOR, UIType::EDITOR_BUTTON, RENDER_ORDER::_UI_);
        CreateUIElement(btn_AddTile, "Btn_RemoveTile", m_ButtonConfig, GAME_STATE::EDITOR, UIType::EDITOR_BUTTON, RENDER_ORDER::_UI_);
    }
}

void ECSFactory::CreateUIElement(Entity entity, const string& btnName, const json& buttonConfig, GAME_STATE state, UIType uiType, RENDER_ORDER renderOrder)
{
    entity = coordinator.CreateEntity();

    switch (state)
    {
    case GAME_STATE::EDITOR:
        coordinator.AddComponent(entity, Editor{});
        coordinator.AddComponent(entity, UIComponent{uiType});
        break;
    case GAME_STATE::GAME:
        coordinator.AddComponent(entity, UIComponent{uiType});
        break;
    case GAME_STATE::MENU:
        coordinator.AddComponent(entity, UIComponent{uiType});
        break;
    default:
        break;
    }

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

    coordinator.AddComponent(entity, Renderer{renderOrder});
    coordinator.m_RenderSystem->AddEntity(entity);
}

void ECSFactory::RegisterCommonSystem()
{
    if (coordinator.m_TilemapSystem == nullptr)
    {
        coordinator.m_TilemapSystem = coordinator.RegisterSystem<TilemapSystem>();
        {
            Signature signature;
            signature.set(coordinator.GetComponentTypeUniqueIndex<Tilemap>());

            coordinator.SetSignature<TilemapSystem>(signature);
        }
        coordinator.m_TilemapSystem->Init();
    }

    if (coordinator.m_LevelEditorSystem == nullptr)
    {
        coordinator.m_LevelEditorSystem = coordinator.RegisterSystem<LevelEditorSystem>();
        {
            Signature signature;
            signature.set(coordinator.GetComponentTypeUniqueIndex<Editor>());

            coordinator.SetSignature<LevelEditorSystem>(signature);
        }
        coordinator.m_LevelEditorSystem->Init();
    }

    if (coordinator.m_CameraSystem == nullptr)
    {
        coordinator.m_CameraSystem = coordinator.RegisterSystem<CameraSystem>();
        {
            Signature signature;
            signature.set(coordinator.GetComponentTypeUniqueIndex<Camera>());

            coordinator.SetSignature<CameraSystem>(signature);
        }
        coordinator.m_CameraSystem->Init();
    }
}

void ECSFactory::RegisterMenuSystem()
{
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

    coordinator.m_RenderSystem = coordinator.RegisterSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentTypeUniqueIndex<Renderer>());

        coordinator.SetSignature<RenderSystem>(signature);
    }
    coordinator.m_RenderSystem->Init();

    coordinator.m_UISystem = coordinator.RegisterSystem<UISystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentTypeUniqueIndex<UIComponent>());

        coordinator.SetSignature<UISystem>(signature);
    }
    coordinator.m_UISystem->Init();

    if (coordinator.m_InputSystem == nullptr)
    {
        
    }
    coordinator.m_InputSystem = coordinator.RegisterSystem<InputSystem>();
    {
        Signature signature;
        signature.set(coordinator.GetComponentTypeUniqueIndex<InPut>());

        coordinator.SetSignature<InputSystem>(signature);
    }
    coordinator.m_InputSystem->Init();
}

void ECSFactory::RegisterGameSystem()
{
    // coordinator.m_PlayerControllerSystem = coordinator.RegisterSystem<PlayerControllerSystem>();
    // {
    //     Signature signature;

    //     // set a subsystem's unique Signature
    //     signature.set(coordinator.GetComponentTypeUniqueIndex<Transform>());
    //     signature.set(coordinator.GetComponentTypeUniqueIndex<Player>());

    //     // here, set a unique signature based on the component attached
    //     coordinator.SetSignature<PlayerControllerSystem>(signature);
    // }
    // coordinator.m_PlayerControllerSystem->Init();

    coordinator.m_ControllerSystem = coordinator.RegisterSystem<ControllerSystem>();
    {
        Signature signature;

        // here, set a unique signature based on the component attached
        coordinator.SetSignature<ControllerSystem>(signature);
    }
    coordinator.m_ControllerSystem->Init();

    coordinator.getGameplaySystem() = coordinator.RegisterSystem<GameplaySystem>();
    {
        Signature signature;

        signature.set(coordinator.GetComponentTypeUniqueIndex<Player>());

        // here, set a unique signature based on the component attached
        coordinator.SetSignature<GameplaySystem>(signature);
    }

    coordinator.m_ScriptingSystem = coordinator.RegisterSystem<ScriptingSystem>();
    {
        Signature signature;

        // set a subsystem's unique Signature
        signature.set(coordinator.GetComponentTypeUniqueIndex<Script>());

        // here, set a unique signature based on the component attached
        coordinator.SetSignature<ScriptingSystem>(signature);
    }
    coordinator.m_ScriptingSystem->Init();
}

void ECSFactory::RegisterMenuEntity()
{
    CreateMenuUI();
}

void ECSFactory::RegisterCommonEntity()
{
    CreateTilemapFromJSON();

    CreateEditorUI();
}

void ECSFactory::CreateEnemyFromJSON()
{
    if (FileReader::GetInstance().LoadJSONFile(COMPONENT_CONFIG))
    {
        // get config object
        auto config = FileReader::GetInstance().GetConfig(COMPONENT_CONFIG);
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

    if(m_IsConfigFileExist){
        coordinator.AddComponent(camera, Camera{
                coordinator.m_CameraSystem->CreateCamera(
                    m_CameraConfig["cameraX"],
                    m_CameraConfig["cameraY"],
                    m_CameraConfig["viewportWidth"],
                    m_CameraConfig["viewportHeight"],
                    m_CameraConfig["worldWidth"],
                    m_CameraConfig["worldHeight"],
                    m_CameraConfig["edge"]
                )
            });
    }
}
