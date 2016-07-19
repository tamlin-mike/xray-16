#pragma once

#pragma warning(disable:4995)
#include "xrEngine/stdafx.h"
#include "DPlay/dplay8.h"
#pragma warning(default:4995)
#pragma warning( 4 : 4018 )
#pragma warning( 4 : 4244 )
#pragma warning(disable:4505)

#if XRAY_EXCEPTIONS
#	define	THROW(expr)				do {if (!(expr)) {string4096	assertion_info; xrDebug::GatherInfo(assertion_info, DEBUG_INFO, #expr,   0,   0,0); throw assertion_info;}} while(0)
#	define	THROW2(expr,msg0)		do {if (!(expr)) {string4096	assertion_info; xrDebug::GatherInfo(assertion_info, DEBUG_INFO, #expr,msg0,   0,0); throw assertion_info;}} while(0)
#	define	THROW3(expr,msg0,msg1)	do {if (!(expr)) {string4096	assertion_info; xrDebug::GatherInfo(assertion_info, DEBUG_INFO, #expr,msg0,msg1,0); throw assertion_info;}} while(0)
#else
#	define	THROW					VERIFY
#	define	THROW2					VERIFY2
#	define	THROW3					VERIFY3
#endif

#pragma region
#include "xrEngine/gamefont.h"
#include "xrEngine/xr_object.h"
#include "xrEngine/IGame_Level.h"
#include "xrPhysics/xrPhysics.h"
#include "xrPhysics/PhysicsShell.h"
#include "xrServerEntities/smart_cast.h"
#include "Common/LevelStructure.hpp"
#include "Common/object_broker.h"
#include "Actor.h"
#include "alife_smart_terrain_task.h"
#include "alife_abstract_registry.h"
#include "alife_graph_registry.h"
#include "alife_simulator.h"
#include "alife_storage_manager.h"
#include "attachable_item.h"
#include "abstract_location_selector.h"
#include "action_planner.h"
//#include "dynamic_obstacles_avoider.h" // included by stalker_movement_manager_obstacles.h
#include "Explosive.h"
#include "HudItem.h"
#include "Inventory.h"
#include "Level.h"
#include "memory_manager.h"
#include "object_handler.h"
#include "object_handler_planner.h"
#include "object_manager.h"
#include "obsolete_queue.h"
#include "obstacles_query.h"
#include "patrol_path_manager.h"
#include "PdaMsg.h"
#include "PhysicsShellHolder.h"
#include "PHCollisionDamageReceiver.h"
#include "PHCommander.h"
#include "PHDebug.h"
#include "PHDestroyable.h"
#include "PHDestroyableNotificate.h"
#include "PHSkeleton.h"
#include "PHSoundPlayer.h"
#include "space_restrictor.h"
#include "stalker_animation_manager.h"
//#include "stalker_movement_params.h" // included by stalker_movement_manager_base.h
//#include "stalker_movement_manager_base.h" // included by stalker_movement_manager_obstacles.h
//#include "stalker_movement_manager_obstacles.h" // included by stalker_movement_manager_smart_cover.h
#include "stalker_movement_manager_smart_cover.h"
#include "state_arguments_functions.h"
//#include "static_obstacles_avoider.h" // include by dynamic_obstacles_avoider.h
#include "steering_behaviour.h"
#include "string_table.h"
#include "script_game_object.h"
#include "smart_cover.h"
#include "smart_cover_detail.h"
#include "sound_player.h"
#include "Spectator.h"
#include "team_hierarchy_holder.h"
#include "Tracer.h"
#include "UICursor.h"
#include "UIGameCTA.h"
#include "ui_defs.h"
#include "UIGameCustom.h"
#include "UIStaticItem.h"
#include "visual_memory_manager.h"
#include "Weapon.h"
#include "WeaponCustomPistol.h"
//#include "WeaponMagazined.h"
#include "xr_time.h"
#include "ai/monsters/basemonster/base_monster.h"
#include "ui/Restrictions.h"
#include "ui/UI_IB_Static.h"
#include "ui/UI3tButton.h"
#include "ui/UIButton.h"
#include "ui/UIBuyWndBase.h"
#include "ui/UIBuyWndShared.h"
#include "ui/UICellItem.h"
#include "ui/UICustomEdit.h"
#include "ui/UIDialogWnd.h"
#include "ui/UIEditBox.h"
#include "ui/UIFrameLineWnd.h"
#include "ui/UIFrameWindow.h"
#include "ui/UIGameLog.h"
#include "ui/UIHelper.h"
#include "ui/UIHint.h"
#include "ui/UIInteractiveBackground.h"
#include "ui/UIInventoryUtilities.h"
#include "ui/UIListBox.h"
#include "ui/UIMainIngameWnd.h"
#include "ui/UIProgressBar.h"
#include "ui/UIOptionsItem.h"
#include "ui/UIScrollView.h"
//#include "ui/UIStatic.h"
#include "ui/UISubLine.h"
#include "ui/UIXmlInit.h"
#include "Include/xrRender/Kinematics.h"
#include "xrAICore/Navigation/graph_abstract.h"
#include "xrAICore/Navigation/ai_object_location.h"
#include "xrCore/_vector3d_ext.h"
#include "xrCore/Crypto/xr_dsa_signer.h"
#include "xrCore/Crypto/xr_dsa_verifyer.h"
#include "xrEngine/CameraBase.h"
#include "xrEngine/CustomHUD.h"
#include "xrEngine/Effector.h"
#include "xrEngine/EffectorPP.h"
#include "xrEngine/GameMtlLib.h"
#include "xrEngine/LightAnimLibrary.h"
#include "xrNetServer/NET_Messages.h"
#include "xrPhysics/PHObject.h"
#include "xrPhysics/PHUpdateObject.h"
#include "xrServerEntities/alife_monster_brain.h"
#pragma endregion Bloat galore!
