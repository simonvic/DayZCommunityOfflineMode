static string COM_FormatFloat( float value, int decimals ) 
{
    if ( !value.ToString().Contains(".") ) return value.ToString();
	
    string result = "";
    array<string> output = new array<string>;
	
    value.ToString().Split(".", output);
	
    if ( output.Count() == 0 ) return value.ToString();
	
    if ( decimals == 0 ) return output.Get(0);
	
    string right = output.Get(1).Substring(0, decimals);
    result = output.Get(0) + "." + right;
    return result;
}

static string COM_VectorToString( vector vec )
{
    string result = vec.ToString();
    result.Replace( "<", "" );
    result.Replace( ">", "" );
    result.Replace( ",", "" );
	
    return result;
}

static string COM_VectorToString( vector vec, int decimals ) 
{
    string result = "";
    result = COM_FormatFloat(vec[0], decimals) + "|" + COM_FormatFloat(vec[1], decimals) + "|" + COM_FormatFloat(vec[2], decimals);
	
    return result;
}

static TStringArray COM_GetChildrenFromBaseClass( string strConfigName, string strBaseClass )
{
    string child_name = "";
    int count = GetGame().ConfigGetChildrenCount ( strConfigName );
    TStringArray class_names = new TStringArray;
	
    for (int p = 0; p < count; p++)
    {
        GetGame().ConfigGetChildName ( strConfigName, p, child_name );
		
        if ( GetGame().IsKindOf(child_name, strBaseClass ) && ( child_name != strBaseClass ) )
        {
            class_names.Insert(child_name);
		}
	}
	
    return class_names;
}

static TVectorArray COM_GetSpawnPoints()
{
    return { "15135.1 0 13901.1", "15017.8 0 13892.4", "14887.1 0 14547.9", "14749.7 0 13248.7",
		"14697.6 0 13418.4", "14537.3 0 14755.7", "14415.3 0 14025.2", "14338.0 0 12859.5",
		"14263.8 0 12748.7", "14172.2 0 12304.9", "14071.4 0 12033.3", "14054.9 0 11341.3",
		"14017.8 0 2959.1", "13905.5 0 12489.7", "13852.4 0 11686.0", "13846.6 0 12050.0",
		"13676.0 0 12262.1", "13617.4 0 12759.8", "13610.1 0 11223.6", "13594.3 0 4064.0",
		"13587.8 0 6026.5", "13571.1 0 3056.8", "13552.6 0 4653.7", "13529.9 0 3968.3",
		"13520.8 0 4223.7", "13504.0 0 5004.5", "13476.7 0 6136.3", "13441.6 0 5262.2",
		"13426.6 0 5747.3", "13416.8 0 11840.4", "13400.8 0 4120.7", "13395.8 0 5902.8",
		"13385.0 0 3946.6", "13374.4 0 6454.3", "13367.1 0 10837.1", "13366.3 0 4906.0",
		"13337.1 0 5120.8", "13326.7 0 5489.1", "13312.7 0 6771.1", "13288.7 0 11415.1",
		"13261.6 0 11785.2", "13171.6 0 6534.8", "13159.8 0 5401.7", "13155.2 0 5475.2",
		"13084.9 0 7938.6", "13056.8 0 4848.5", "13048.1 0 8357.6", "13048.1 0 3867.7",
		"12991.7 0 7287.1", "12983.0 0 5539.1", "12978.9 0 9727.8", "12950.2 0 5226.7",
		"12942.1 0 8393.1", "12891.5 0 3673.9", "12628.7 0 10495.2", "12574.3 0 3592.8",
	"12566.3 0 6682.6", "12465.2 0 8009.0", "12354.5 0 3480.0", "13262.8 0 7225.8" };
}

static set< Object > COM_GetObjectsAt( vector from, vector to, Object ignore = NULL, float radius = 0.5, Object with = NULL )
{
    vector contact_pos;
    vector contact_dir;
    int contact_component;
	
    set< Object > geom = new set< Object >;
    set< Object > view = new set< Object >;
	
    DayZPhysics.RaycastRV( from, to, contact_pos, contact_dir, contact_component, geom, with, ignore, false, false, ObjIntersectGeom, radius );
    DayZPhysics.RaycastRV( from, to, contact_pos, contact_dir, contact_component, view, with, ignore, false, false, ObjIntersectView, radius );
	
    if ( geom.Count() > 0 ) 
    {
        return geom;
	}
    if ( view.Count() > 0 ) 
    {
        return view;
	}
    return NULL;
}

static Object COM_GetPointerObject( Object ignore = NULL, float radius = 0.5, Object with = NULL )
{
    vector dir = GetGame().GetPointerDirection();
	
    vector from = GetGame().GetCurrentCameraPosition();
	
    vector to = from + ( dir * 10000 );
	
    auto objs = COM_GetObjectsAt( from, to, ignore, radius, with );
	
    if( objs.Count() > 0 )
    {
        return objs[ 0 ];
	}
	
    return NULL;
}

static Object COM_GetCursorObject()
{
    vector rayStart = GetGame().GetCurrentCameraPosition();
    vector rayEnd = rayStart + GetGame().GetCurrentCameraDirection() * 10000;
	
    auto objs = COM_GetObjectsAt( rayStart, rayEnd );
	
    if( objs.Count() > 0 )
    {
        return objs[ 0 ];
	}
	
    return NULL;
}

static vector COM_GetPointerPos()
{
    if ( !COM_GetPB() )
    {
        return "0 0 0";
	}
	
    vector dir = GetGame().GetPointerDirection();
	
    vector from = GetGame().GetCurrentCameraPosition();
	
    vector to = from + ( dir * 10000 );
	
    vector rayStart = from;
    vector rayEnd = to;
    vector hitPos;
    vector hitNormal;
    int hitComponentIndex;
    DayZPhysics.RaycastRV(rayStart, rayEnd, hitPos, hitNormal, hitComponentIndex, NULL, NULL, COM_GetPB());
	
    return hitPos;
}

static vector COM_GetCursorPos()
{
    if ( !COM_GetPB() )
    {
        return "0 0 0";
	}
	
    vector rayStart = GetGame().GetCurrentCameraPosition();
    vector rayEnd = rayStart + GetGame().GetCurrentCameraDirection() * 10000;
    vector hitPos;
    vector hitNormal;
    int hitComponentIndex;
    DayZPhysics.RaycastRV(rayStart, rayEnd, hitPos, hitNormal, hitComponentIndex, NULL, NULL, COM_GetPB());
	
    return hitPos;
}

static void COM_Message( string txt ) 
{
    COM_GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", txt, ""));
}

static Weapon COM_GetWeaponInHands()
{
    Weapon weapon_in_hands;
    if( COM_GetPB() && COM_GetPB().GetItemInHands() ) Class.CastTo(weapon_in_hands,  COM_GetPB().GetItemInHands());
	
    return weapon_in_hands;
}

static MissionBase COM_GetMission()
{
    return MissionBase.Cast( GetGame().COM_GetMission() );
}

static CommunityOfflineClient COM_GetClientMission()
{
    return CommunityOfflineClient.Cast( GetGame().COM_GetMission() );
}

static CommunityOfflineServer COM_GetServerMission()
{
    return CommunityOfflineServer.Cast( GetGame().COM_GetMission() );
}

static PlayerBase COM_GetPB()
{
    return PlayerBase.Cast( GetGame().GetPlayer() );
}

static bool COM_SHIFT()
{
    return( ( KeyState( KeyCode.KC_LSHIFT ) > 0 ) || ( KeyState( KeyCode.KC_RSHIFT ) > 0 ) );
}

static bool COM_CTRL()
{
    return( ( KeyState( KeyCode.KC_LCONTROL ) > 0 ) || ( KeyState( KeyCode.KC_RCONTROL ) > 0 ) );
}

static bool COM_ALT()
{
    return( ( KeyState( KeyCode.KC_LMENU ) > 0 ) || ( KeyState( KeyCode.KC_RMENU ) > 0 ) );
}

static bool COM_WINKEY()
{
    return( ( KeyState( KeyCode.KC_LWIN ) > 0 ) || ( KeyState( KeyCode.KC_RWIN ) > 0 ) );
}

static PlayerBase COM_CreateCustomDefaultCharacter(){

    PlayerBase oPlayer = PlayerBase.Cast( GetGame().CreatePlayer( NULL, "SurvivorM_Mirek" , COM_GetSpawnPoints().GetRandomElement(), 0, "NONE") );
	GameInventory inv = oPlayer.GetInventory();

    createItem(inv, "MilitaryBeret_Red");
    createItem(inv, "AviatorGlasses");

    createItem(inv, "TShirt_Green");
    createItem(inv, "PressVest_Blue");

    createItem(inv, "TacticalGloves_Beige");
    createItem(inv, "MilitaryBelt");
    createItem(inv, "AliceBag_Green");

    createItem(inv, "CargoPants_Blue");

    EntityAI boots = createItem(inv, "MilitaryBoots_Black" );
    EntityAI knife = createAttachment(boots, "HuntingKnife" );
	
    Weapon_Base vss = createWeapon(inv, "VSS");
    addBattery(createAttachment(vss, "KobraOptic"));
    createItem(inv, "Mag_VSS_10Rnd");

    Weapon_Base mosin = createWeapon(inv, "Mosin9130");
    createAttachment(mosin, "PUScopeoptic");

	Weapon_Base fal = createWeapon(inv, "FAL");
    addBattery(createAttachment(fal, "M68Optic"));
    createAttachment(fal, "Fal_FoldingBttstck");
    createItem(inv, "Mag_FAL_20Rnd");

    Weapon_Base m4 = createWeapon(inv, "M4A1");
    createAttachment(m4, "M4_Suppressor");
    createAttachment(m4, "M4_OEBttstck");
    createAttachment(m4, "M4_RISHndgrd");
    createAttachment(m4, "M4_Suppressor");
    addBattery(createAttachment(m4, "M4_T3NRDSOptic"));
    createItem(inv, "Mag_STANAGCoupled_30Rnd");

    Weapon_Base ak74 = createWeapon(inv, "AK74");
    createAttachment(ak74, "AK_PlasticBttstck");
    createAttachment(ak74, "AK_PlasticHndgrd");
    createItem(inv, "Mag_AK74_30Rnd_Black");

    Weapon_Base mp5 = createWeapon(inv, "MP5K");
    addBattery(createAttachment(mp5, "ReflexOptic"));
    createAttachment(mp5, "MP5_Compensator");
    createAttachment(mp5, "MP5k_StockBttstck");
    createAttachment(mp5, "MP5_RailHndgrd");
    addBattery(createAttachment(mp5, "UniversalLight"));
    createItem(inv, "Mag_MP5_30Rnd");
    

    Weapon_Base deagle = createWeapon(inv, "Deagle");
    createAttachment(deagle, "PistolOptic");
    createItem(inv, "Mag_Deagle_9rnd");
    addBattery(createItem(inv,"FNP45_MRDSOptic"));

    addBattery(createAttachment(createWeapon(inv, "Glock19"),"FNP45_MRDSOptic"));
    createItem(inv, "Mag_Glock_15Rnd");

    oPlayer.PredictiveTakeEntityToHands( deagle );
	
    oPlayer.SetQuickBarEntityShortcut( m4, 0, true );
    oPlayer.SetQuickBarEntityShortcut( ak74, 1, true );
	oPlayer.SetQuickBarEntityShortcut( deagle, 2, true );
	oPlayer.SetQuickBarEntityShortcut( mosin, 3, true );
	oPlayer.SetQuickBarEntityShortcut( knife, 4, true );
	oPlayer.SetQuickBarEntityShortcut( mp5, 5, true );

    Clothing weaponBag = GetGame().CreateObject( "AliceBag_Black", oPlayer.GetPosition());
    GameInventory weaponBagInv = weaponBag.GetInventory();
    Weapon_Base akm = createWeapon(weaponBagInv, "AKM");
    createAttachment(akm, "AK74_WoodBttstck");
    createAttachment(akm, "AK74_Hndgrd");
    addBattery(createAttachment(akm, "PSO1Optic"));
    createItem(weaponBagInv, "Mag_AKM_Drum75Rnd");

    createWeapon(weaponBagInv, "Mp133Shotgun");

    createWeapon(weaponBagInv, "UMP45");
    createItem(weaponBagInv, "Mag_UMP_25Rnd");
    createAttachment(createWeapon(weaponBagInv, "Winchester70"), "HuntingOptic");

    EntityAI stove = GetGame().CreateObject( "PortableGasStove", oPlayer.GetPosition());
	EntityAI pot = stove.GetInventory().CreateAttachment("Pot");
    pot.GetInventory().CreateEntityInCargo("Rice");
    pot.GetInventory().CreateEntityInCargo("Potato");
    pot.GetInventory().CreateEntityInCargo("AgaricusMushroom");
    pot.GetInventory().CreateEntityInCargo("AgaricusMushroom");

    stove.GetInventory().CreateAttachment("LargeGasCanister");

    return oPlayer;
}

static void addBattery(EntityAI item){
    createAttachment(item, "Battery9V");
}

static EntityAI createAttachment(EntityAI item, string attachment){
    return item.GetInventory().CreateAttachment(attachment);
}

static Weapon_Base createWeapon(GameInventory inventory, string item){
    return Weapon_Base.Cast(createItem(inventory,item));
}

static EntityAI createItem(GameInventory inventory, string item){
    return inventory.CreateInInventory(item);
}

static string COM_FileAttributeToString( FileAttr attr )
{
    string fileType = "";
    if ( attr & FileAttr.DIRECTORY )
    {
        fileType = fileType + "DIRECTORY";
	}
    if ( attr & FileAttr.HIDDEN )
    {
	fileType = fileType + "HIDDEN";
    }
    if ( attr & FileAttr.READONLY )
    {
	fileType = fileType + "READONLY";
    }
    if ( attr & FileAttr.INVALID )
    {
	fileType = fileType + "INVALID";
    }
    return fileType;
	}
	
	static vector COM_SnapToGround(vector pos)
	{
    float pos_x = pos[0];
    float pos_z = pos[2];
    float pos_y = GetGame().SurfaceY( pos_x, pos_z );
    vector tmp_pos = Vector( pos_x, pos_y, pos_z );
    tmp_pos[1] = tmp_pos[1] + pos[1];
	
    return tmp_pos;
	}
	
	static bool m_COM_GodMode; // move these to player saves? Edit: Jacob says "yes"
	static bool m_COM_OldAiming;
	static bool COM_bc_Visible;
	
	static void COM_SnapToGroundNew( Object object ) 
	{
    vector pos = object.GetPosition();
    pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
    
    vector clippingInfo[2];
    vector objectBBOX[2];
    
    object.GetCollisionBox( objectBBOX );
    object.ClippingInfo( clippingInfo );
	
    //float clipY = objectBBOX[1][1] / 2.0//- clippingInfo[0][1];
    //pos[1] = pos[1] + objectBBOX[1][1] - clipY;
    pos[1] = pos[1] + clippingInfo[1][1] / 2.0;//objectBBOX[0][1] - clipY
	
    object.SetPosition(pos);
	
    COM_ForceTargetCollisionUpdate( object );
	}
	
	static void COM_ForceTargetCollisionUpdate( Object oObj )
	{
    if ( !oObj ) return;
	
    vector roll = oObj.GetOrientation();
    roll [ 2 ] = roll [ 2 ] - 1;
    oObj.SetOrientation( roll );
    roll [ 2 ] = roll [ 2 ] + 1;
    oObj.SetOrientation( roll );
	}
	
	static void COM_ToggleCursor()
	{
    if ( GetGame().GetInput().HasGameFocus( INPUT_DEVICE_MOUSE ) )
    {
	GetGame().GetInput().ChangeGameFocus( 1 );
	GetGame().GetUIManager().ShowUICursor( true );
    }
    else
    {
	GetGame().GetUIManager().ShowUICursor( false );
	GetGame().GetInput().ResetGameFocus();
    }
	}
	
	/*
    Token types:
	0 - error, no token
	1 - defined token (special characters etc. . / * )
	2 - quoted string. Quotes are removed -> TODO
	3 - alphabetic string
	4 - number
	5 - end of line -> TODO
	*/
	static bool COM_CheckStringType( string str, int type ) 
	{
    for(int i = 0; i<str.Length(); i++ ) 
    {
	string character = str.Get(i);
	string token;
	int result = character.ParseStringEx(token);
	if ( result == type ) return true;
    }
    return false;
	}
	
	string COM_GetRandomChildFromBaseClass( string strConfigName, string strBaseClass, int minScope = -1 )
	{
    string child_name = "";
    int count = GetGame().ConfigGetChildrenCount ( strConfigName );
    array< string > class_names = new array<string>;
	
    for ( int p = 0; p < count; p++ )
    {
	GetGame().ConfigGetChildName( strConfigName, p, child_name );
	
	if( ( minScope != -1 ) && ( GetGame().ConfigGetInt( strConfigName + " " + child_name + " scope" ) < minScope ) ) continue;
	
	if ( GetGame().IsKindOf( child_name, strBaseClass ) && ( child_name != strBaseClass ) )
	{
	class_names.Insert( child_name );
	}
    }
	
    return class_names.GetRandomElement();
	}	