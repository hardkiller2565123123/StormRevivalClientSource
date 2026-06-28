package script.freebtl_prac
{
   import Struct.MessageParam;
   import flash.external.*;
   
   public class menu_param
   {
      
      public const PLATE_TYPE_NORMAL:int = 0;
      
      public const PLATE_TYPE_SUPPORT:int = 1;
      
      public const PLATE_TYPE_RESET:int = 2;
      
      public const ITEM_CMN_LIFE:int = 0;
      
      public const ITEM_CMN_CHAKRA:int = 1;
      
      public const ITEM_CMN_SUPPORT:int = 2;
      
      public const ITEM_CMN_STORM:int = 3;
      
      public const ITEM_CMN_DODGE:int = 4;
      
      public const ITEM_CMN_ITEM:int = 5;
      
      public const ITEM_CMN_AWAKE:int = 6;
      
      public const ITEM_CMN_DAMAGE_RATIO:int = 7;
      
      public const ITEM_CMN_NATURAL_EXPRESSION:int = 8;
      
      public const ITEM_CMN_RESET:int = 9;
      
      public const ITEM_CMN_NUM:int = 10;
      
      public const ITEM_COM_ACTION:int = 0;
      
      public const ITEM_COM_STRENGTH:int = 1;
      
      public const ITEM_COM_GUARD:int = 2;
      
      public const ITEM_COM_DODGE:int = 3;
      
      public const ITEM_COM_RECOVER:int = 4;
      
      public const ITEM_COM_JUMP:int = 5;
      
      public const ITEM_COM_THROW:int = 6;
      
      public const ITEM_COM_PROJ:int = 7;
      
      public const ITEM_COM_CHAKRA_PROJ:int = 8;
      
      public const ITEM_COM_SKILL:int = 9;
      
      public const ITEM_COM_TOOL:int = 10;
      
      public const ITEM_COM_NINJA_MOVE:int = 11;
      
      public const ITEM_COM_NINJA_DASH:int = 12;
      
      public const ITEM_COM_CHAKRA_DASH:int = 13;
      
      public const ITEM_COM_CHARGE_DASH:int = 14;
      
      public const ITEM_COM_SUP_SKILL:int = 15;
      
      public const ITEM_COM_COUNTER:int = 16;
      
      public const ITEM_COM_GUARD_BREAK:int = 17;
      
      public const ITEM_COM_SPSKILL:int = 18;
      
      public const ITEM_COM_TEAM_SPSKILL:int = 19;
      
      public const ITEM_COM_AWAKE:int = 20;
      
      public const ITEM_COM_LEADER_CHANGE:int = 21;
      
      public const ITEM_COM_SUPORT_ACTION:int = 22;
      
      public const ITEM_COM_RESET:int = 23;
      
      public const ITEM_COM_NUM:int = 24;
      
      public var MESSAGE_INFINITY:String;
      
      public var MESSAGE_NORMAL:String;
      
      public var MESSAGE_INVINCIBLE:String;
      
      public var MESSAGE_ALWAYS:String;
      
      public var MESSAGE_NOACTIVE:String;
      
      public var MESSAGE_ACTIVE:String;
      
      public var MESSAGE_NOTADD:String;
      
      public var MESSAGE_RESET:String;
      
      public var MESSAGE_NOACTION:String;
      
      public var MESSAGE_COM:String;
      
      public var MESSAGE_2PCTRL:String;
      
      public var MESSAGE_USE:String;
      
      public var MESSAGE_NOTUSE:String;
      
      public var MESSAGE_ENROUTE:String;
      
      public var MESSAGE_ENABLE:String;
      
      public var MESSAGE_DISABLE:String;
      
      public var MESSAGE_NOTCHANGE:String;
      
      public var MESSAGE_VERY_EASY:String;
      
      public var MESSAGE_EASY:String;
      
      public var MESSAGE_STR_NORMAL:String;
      
      public var MESSAGE_HARD:String;
      
      public var MESSAGE_VERY_HARD:String;
      
      public var MESSAGE_AWAKE:String;
      
      public var ItemCMN:Array;
      
      public var ItemCOM:Array;
      
      public function menu_param()
      {
         super();
      }
      
      public function InitParam() : void
      {
         this.MESSAGE_INFINITY = String(ExternalInterface.call("MessageConvert","practice_infinity"));
         this.MESSAGE_NORMAL = String(ExternalInterface.call("MessageConvert","practice_normal"));
         this.MESSAGE_INVINCIBLE = String(ExternalInterface.call("MessageConvert","practice_invincible"));
         this.MESSAGE_ALWAYS = String(ExternalInterface.call("MessageConvert","practice_always"));
         this.MESSAGE_NOACTIVE = String(ExternalInterface.call("MessageConvert","practice_noActive"));
         this.MESSAGE_ACTIVE = String(ExternalInterface.call("MessageConvert","practice_active"));
         this.MESSAGE_NOTADD = String(ExternalInterface.call("MessageConvert","practice_notAdd"));
         this.MESSAGE_RESET = String(ExternalInterface.call("MessageConvert","practice_reset"));
         this.MESSAGE_NOACTION = String(ExternalInterface.call("MessageConvert","practice_noAction"));
         this.MESSAGE_COM = String(ExternalInterface.call("MessageConvert","tournament_041"));
         this.MESSAGE_2PCTRL = String(ExternalInterface.call("MessageConvert","practice_2pCtrl"));
         this.MESSAGE_USE = String(ExternalInterface.call("MessageConvert","practice_use"));
         this.MESSAGE_NOTUSE = String(ExternalInterface.call("MessageConvert","practice_notuse"));
         this.MESSAGE_ENROUTE = String(ExternalInterface.call("MessageConvert","practice_scrFont_010"));
         this.MESSAGE_ENABLE = String(ExternalInterface.call("MessageConvert","practice_scrFont_020"));
         this.MESSAGE_DISABLE = String(ExternalInterface.call("MessageConvert","practice_scrFont_021"));
         this.MESSAGE_NOTCHANGE = String(ExternalInterface.call("MessageConvert","practice_scrFont_013"));
         this.MESSAGE_VERY_EASY = String(ExternalInterface.call("MessageConvert","characterselect_027"));
         this.MESSAGE_EASY = String(ExternalInterface.call("MessageConvert","characterselect_028"));
         this.MESSAGE_STR_NORMAL = String(ExternalInterface.call("MessageConvert","characterselect_029"));
         this.MESSAGE_HARD = String(ExternalInterface.call("MessageConvert","characterselect_030"));
         this.MESSAGE_VERY_HARD = String(ExternalInterface.call("MessageConvert","characterselect_031"));
         var _loc1_:MessageParam = new MessageParam();
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_020"));
         this.MESSAGE_AWAKE = _loc1_.m_msg;
         this.ItemCMN = new Array(this.ITEM_CMN_NUM);
         this.ItemCMN[this.ITEM_CMN_LIFE] = new Object();
         this.ItemCMN[this.ITEM_CMN_LIFE].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCMN[this.ITEM_CMN_LIFE].select = [this.MESSAGE_INFINITY,this.MESSAGE_NORMAL,this.MESSAGE_AWAKE];
         this.ItemCMN[this.ITEM_CMN_LIFE].help = String(ExternalInterface.call("MessageConvert","practice_scrFontCmnLife"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","practice_lifeGauge"));
         this.ItemCMN[this.ITEM_CMN_LIFE].title = _loc1_.m_cmd;
         this.ItemCMN[this.ITEM_CMN_LIFE].index = this.ITEM_CMN_LIFE;
         this.ItemCMN[this.ITEM_CMN_CHAKRA] = new Object();
         this.ItemCMN[this.ITEM_CMN_CHAKRA].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCMN[this.ITEM_CMN_CHAKRA].select = [this.MESSAGE_NORMAL,this.MESSAGE_INFINITY];
         this.ItemCMN[this.ITEM_CMN_CHAKRA].help = String(ExternalInterface.call("MessageConvert","practice_scrFontCmnChakra"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","practice_chakraGauge"));
         this.ItemCMN[this.ITEM_CMN_CHAKRA].title = _loc1_.m_cmd;
         this.ItemCMN[this.ITEM_CMN_CHAKRA].index = this.ITEM_CMN_CHAKRA;
         this.ItemCMN[this.ITEM_CMN_SUPPORT] = new Object();
         this.ItemCMN[this.ITEM_CMN_SUPPORT].plate = this.PLATE_TYPE_SUPPORT;
         this.ItemCMN[this.ITEM_CMN_SUPPORT].select = [this.MESSAGE_NORMAL,this.MESSAGE_INFINITY];
         this.ItemCMN[this.ITEM_CMN_SUPPORT].help = String(ExternalInterface.call("MessageConvert","practice_scrFontCmnSupGauge"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","practice_supGauge"));
         this.ItemCMN[this.ITEM_CMN_SUPPORT].title = _loc1_.m_cmd;
         this.ItemCMN[this.ITEM_CMN_SUPPORT].index = this.ITEM_CMN_SUPPORT;
         this.ItemCMN[this.ITEM_CMN_STORM] = new Object();
         this.ItemCMN[this.ITEM_CMN_STORM].plate = this.PLATE_TYPE_SUPPORT;
         this.ItemCMN[this.ITEM_CMN_STORM].select = [this.MESSAGE_NORMAL,this.MESSAGE_INFINITY,this.MESSAGE_NOTADD,this.MESSAGE_RESET];
         this.ItemCMN[this.ITEM_CMN_STORM].help = String(ExternalInterface.call("MessageConvert","practice_scrFontCmnTeam"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_033"));
         this.ItemCMN[this.ITEM_CMN_STORM].title = _loc1_.m_msg;
         this.ItemCMN[this.ITEM_CMN_STORM].index = this.ITEM_CMN_STORM;
         this.ItemCMN[this.ITEM_CMN_DODGE] = new Object();
         this.ItemCMN[this.ITEM_CMN_DODGE].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCMN[this.ITEM_CMN_DODGE].select = [this.MESSAGE_NORMAL,this.MESSAGE_INFINITY];
         this.ItemCMN[this.ITEM_CMN_DODGE].help = String(ExternalInterface.call("MessageConvert","practice_scrFontCmnDodge"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","practice_dodgeGauge"));
         this.ItemCMN[this.ITEM_CMN_DODGE].title = _loc1_.m_cmd;
         this.ItemCMN[this.ITEM_CMN_DODGE].index = this.ITEM_CMN_DODGE;
         this.ItemCMN[this.ITEM_CMN_ITEM] = new Object();
         this.ItemCMN[this.ITEM_CMN_ITEM].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCMN[this.ITEM_CMN_ITEM].select = [this.MESSAGE_INFINITY,this.MESSAGE_NORMAL];
         this.ItemCMN[this.ITEM_CMN_ITEM].help = String(ExternalInterface.call("MessageConvert","practice_scrFontCmnItem"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","MSG_NinjaTool"));
         this.ItemCMN[this.ITEM_CMN_ITEM].title = _loc1_.m_cmd;
         this.ItemCMN[this.ITEM_CMN_ITEM].index = this.ITEM_CMN_ITEM;
         this.ItemCMN[this.ITEM_CMN_AWAKE] = new Object();
         this.ItemCMN[this.ITEM_CMN_AWAKE].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCMN[this.ITEM_CMN_AWAKE].select = [this.MESSAGE_NORMAL,this.MESSAGE_INFINITY];
         this.ItemCMN[this.ITEM_CMN_AWAKE].help = String(ExternalInterface.call("MessageConvert","practice_scrFont_011"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","practice_Item_003"));
         this.ItemCMN[this.ITEM_CMN_AWAKE].title = _loc1_.m_cmd;
         this.ItemCMN[this.ITEM_CMN_AWAKE].index = this.ITEM_CMN_AWAKE;
         this.ItemCMN[this.ITEM_CMN_DAMAGE_RATIO] = new Object();
         this.ItemCMN[this.ITEM_CMN_DAMAGE_RATIO].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCMN[this.ITEM_CMN_DAMAGE_RATIO].select = [this.MESSAGE_ENABLE,this.MESSAGE_DISABLE];
         this.ItemCMN[this.ITEM_CMN_DAMAGE_RATIO].help = String(ExternalInterface.call("MessageConvert","practice_scrFont_014"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","practice_Item_000"));
         this.ItemCMN[this.ITEM_CMN_DAMAGE_RATIO].title = _loc1_.m_cmd;
         this.ItemCMN[this.ITEM_CMN_DAMAGE_RATIO].index = this.ITEM_CMN_DAMAGE_RATIO;
         this.ItemCMN[this.ITEM_CMN_NATURAL_EXPRESSION] = new Object();
         this.ItemCMN[this.ITEM_CMN_NATURAL_EXPRESSION].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCMN[this.ITEM_CMN_NATURAL_EXPRESSION].select = [this.MESSAGE_ENABLE,this.MESSAGE_DISABLE];
         this.ItemCMN[this.ITEM_CMN_NATURAL_EXPRESSION].help = String(ExternalInterface.call("MessageConvert","practice_scrFont_015"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","practice_Item_001"));
         this.ItemCMN[this.ITEM_CMN_NATURAL_EXPRESSION].title = _loc1_.m_cmd;
         this.ItemCMN[this.ITEM_CMN_NATURAL_EXPRESSION].index = this.ITEM_CMN_NATURAL_EXPRESSION;
         this.ItemCMN[this.ITEM_CMN_RESET] = new Object();
         this.ItemCMN[this.ITEM_CMN_RESET].plate = this.PLATE_TYPE_RESET;
         this.ItemCMN[this.ITEM_CMN_RESET].select = [this.MESSAGE_NORMAL,this.MESSAGE_INFINITY];
         this.ItemCMN[this.ITEM_CMN_RESET].help = String(ExternalInterface.call("MessageConvert","practice_scrFontCmnReset"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","practice_resetCmn"));
         this.ItemCMN[this.ITEM_CMN_RESET].title = _loc1_.m_cmd;
         this.ItemCMN[this.ITEM_CMN_RESET].index = this.ITEM_CMN_RESET;
         this.ItemCOM = new Array(this.ITEM_COM_NUM);
         this.ItemCOM[0] = new Object();
         this.ItemCOM[0].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[0].select = [this.MESSAGE_NOACTION,this.MESSAGE_COM,this.MESSAGE_2PCTRL];
         this.ItemCOM[0].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComEnemyAction"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","practice_enemyAction"));
         this.ItemCOM[0].title = _loc1_.m_cmd;
         this.ItemCOM[0].index = this.ITEM_COM_ACTION;
         this.ItemCOM[1] = new Object();
         this.ItemCOM[1].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[1].select = [this.MESSAGE_VERY_EASY,this.MESSAGE_EASY,this.MESSAGE_STR_NORMAL,this.MESSAGE_HARD,this.MESSAGE_VERY_HARD];
         this.ItemCOM[1].help = String(ExternalInterface.call("MessageConvert","practice_scrFont_016"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","characterselect_026"));
         this.ItemCOM[1].title = _loc1_.m_cmd;
         this.ItemCOM[1].index = this.ITEM_COM_STRENGTH;
         this.ItemCOM[2] = new Object();
         this.ItemCOM[2].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[2].select = [this.MESSAGE_NOACTIVE,this.MESSAGE_ENROUTE,this.MESSAGE_ACTIVE];
         this.ItemCOM[2].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComGaurd"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_002"));
         this.ItemCOM[2].title = _loc1_.m_msg;
         this.ItemCOM[2].index = this.ITEM_COM_GUARD;
         this.ItemCOM[3] = new Object();
         this.ItemCOM[3].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[3].select = [this.MESSAGE_NOTUSE,this.MESSAGE_USE];
         this.ItemCOM[3].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComDodge"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_003"));
         this.ItemCOM[3].title = _loc1_.m_msg;
         this.ItemCOM[3].index = this.ITEM_COM_DODGE;
         this.ItemCOM[4] = new Object();
         this.ItemCOM[4].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[4].select = [this.MESSAGE_NOACTIVE,this.MESSAGE_ACTIVE];
         this.ItemCOM[4].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComRecover"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_011"));
         this.ItemCOM[4].title = _loc1_.m_msg;
         this.ItemCOM[4].index = this.ITEM_COM_RECOVER;
         this.ItemCOM[5] = new Object();
         this.ItemCOM[5].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[5].select = [this.MESSAGE_NOACTIVE,this.MESSAGE_ACTIVE];
         this.ItemCOM[5].help = String(ExternalInterface.call("MessageConvert","practice_scrFont_007"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_008"));
         this.ItemCOM[5].title = _loc1_.m_msg;
         this.ItemCOM[5].index = this.ITEM_COM_JUMP;
         this.ItemCOM[6] = new Object();
         this.ItemCOM[6].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[6].select = [this.MESSAGE_NOACTIVE,this.MESSAGE_ACTIVE];
         this.ItemCOM[6].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComThrow"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_005"));
         this.ItemCOM[6].title = _loc1_.m_msg;
         this.ItemCOM[6].index = this.ITEM_COM_THROW;
         this.ItemCOM[7] = new Object();
         this.ItemCOM[7].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[7].select = [this.MESSAGE_NOTUSE,this.MESSAGE_USE];
         this.ItemCOM[7].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComProj"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_007"));
         this.ItemCOM[7].title = _loc1_.m_msg;
         this.ItemCOM[7].index = this.ITEM_COM_PROJ;
         this.ItemCOM[8] = new Object();
         this.ItemCOM[8].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[8].select = [this.MESSAGE_NOTUSE,this.MESSAGE_USE];
         this.ItemCOM[8].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComChakraProj"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_014"));
         this.ItemCOM[8].title = _loc1_.m_msg;
         this.ItemCOM[8].index = this.ITEM_COM_CHAKRA_PROJ;
         this.ItemCOM[9] = new Object();
         this.ItemCOM[9].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[9].select = [this.MESSAGE_NOTUSE,this.MESSAGE_USE];
         this.ItemCOM[9].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComSkill"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_017"));
         this.ItemCOM[9].title = _loc1_.m_msg;
         this.ItemCOM[9].index = this.ITEM_COM_SKILL;
         this.ItemCOM[10] = new Object();
         this.ItemCOM[10].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[10].select = [this.MESSAGE_NOTUSE,this.MESSAGE_USE];
         this.ItemCOM[10].help = String(ExternalInterface.call("MessageConvert","MSG_practice_000"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","MSG_NinjaTool"));
         this.ItemCOM[10].title = _loc1_.m_cmd;
         this.ItemCOM[10].index = this.ITEM_COM_TOOL;
         this.ItemCOM[11] = new Object();
         this.ItemCOM[11].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[11].select = [this.MESSAGE_NOACTIVE,this.MESSAGE_ACTIVE];
         this.ItemCOM[11].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComNinjaMove"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_009"));
         this.ItemCOM[11].title = _loc1_.m_msg;
         this.ItemCOM[11].index = this.ITEM_COM_NINJA_MOVE;
         this.ItemCOM[12] = new Object();
         this.ItemCOM[12].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[12].select = [this.MESSAGE_NOACTIVE,this.MESSAGE_ACTIVE];
         this.ItemCOM[12].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComNinjaDash"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_010"));
         this.ItemCOM[12].title = _loc1_.m_msg;
         this.ItemCOM[12].index = this.ITEM_COM_NINJA_DASH;
         this.ItemCOM[13] = new Object();
         this.ItemCOM[13].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[13].select = [this.MESSAGE_NOACTIVE,this.MESSAGE_ACTIVE];
         this.ItemCOM[13].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComChakraDash"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_015"));
         this.ItemCOM[13].title = _loc1_.m_msg;
         this.ItemCOM[13].index = this.ITEM_COM_CHAKRA_DASH;
         this.ItemCOM[14] = new Object();
         this.ItemCOM[14].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[14].select = [this.MESSAGE_NOACTIVE,this.MESSAGE_ACTIVE];
         this.ItemCOM[14].help = String(ExternalInterface.call("MessageConvert","practice_scrFont_017"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_373"));
         this.ItemCOM[14].title = _loc1_.m_msg;
         this.ItemCOM[14].index = this.ITEM_COM_CHARGE_DASH;
         this.ItemCOM[15] = new Object();
         this.ItemCOM[15].plate = this.PLATE_TYPE_SUPPORT;
         this.ItemCOM[15].select = [this.MESSAGE_NOTUSE,this.MESSAGE_USE];
         this.ItemCOM[15].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComSupSkill"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_022"));
         this.ItemCOM[15].title = _loc1_.m_msg;
         this.ItemCOM[15].index = this.ITEM_COM_SUP_SKILL;
         this.ItemCOM[16] = new Object();
         this.ItemCOM[16].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[16].select = [this.MESSAGE_NOTUSE,this.MESSAGE_USE];
         this.ItemCOM[16].help = String(ExternalInterface.call("MessageConvert","practice_scrFont_000"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_352"));
         this.ItemCOM[16].title = _loc1_.m_msg;
         this.ItemCOM[16].index = this.ITEM_COM_COUNTER;
         this.ItemCOM[17] = new Object();
         this.ItemCOM[17].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[17].select = [this.MESSAGE_NOTUSE,this.MESSAGE_USE];
         this.ItemCOM[17].help = String(ExternalInterface.call("MessageConvert","practice_scrFont_001"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_353"));
         this.ItemCOM[17].title = _loc1_.m_msg;
         this.ItemCOM[17].index = this.ITEM_COM_GUARD_BREAK;
         this.ItemCOM[18] = new Object();
         this.ItemCOM[18].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[18].select = [this.MESSAGE_NOTUSE,this.MESSAGE_USE];
         this.ItemCOM[18].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComSpSkill"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_019"));
         this.ItemCOM[18].title = _loc1_.m_msg;
         this.ItemCOM[18].index = this.ITEM_COM_SPSKILL;
         this.ItemCOM[19] = new Object();
         this.ItemCOM[19].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[19].select = [this.MESSAGE_NOTUSE,this.MESSAGE_USE];
         this.ItemCOM[19].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComTeamSpSkill"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","practice_Item_004"));
         this.ItemCOM[19].title = _loc1_.m_cmd;
         this.ItemCOM[19].index = this.ITEM_COM_TEAM_SPSKILL;
         this.ItemCOM[20] = new Object();
         this.ItemCOM[20].plate = this.PLATE_TYPE_NORMAL;
         this.ItemCOM[20].select = [this.MESSAGE_NOACTIVE,this.MESSAGE_ACTIVE];
         this.ItemCOM[20].help = String(ExternalInterface.call("MessageConvert","practice_scrFont_003"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","practice_Item_003"));
         this.ItemCOM[20].title = _loc1_.m_cmd;
         this.ItemCOM[20].index = this.ITEM_COM_AWAKE;
         this.ItemCOM[21] = new Object();
         this.ItemCOM[21].plate = this.PLATE_TYPE_SUPPORT;
         this.ItemCOM[21].select = [this.MESSAGE_NOTUSE,this.MESSAGE_USE];
         this.ItemCOM[21].help = String(ExternalInterface.call("MessageConvert","practice_scrFont_018"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","commandlist_demo_21"));
         this.ItemCOM[21].title = _loc1_.m_msg;
         this.ItemCOM[21].index = this.ITEM_COM_LEADER_CHANGE;
         this.ItemCOM[22] = new Object();
         this.ItemCOM[22].plate = this.PLATE_TYPE_SUPPORT;
         this.ItemCOM[22].select = [this.MESSAGE_NOTUSE,this.MESSAGE_USE];
         this.ItemCOM[22].help = String(ExternalInterface.call("MessageConvert","practice_scrFont_022"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","practice_Item_002"));
         this.ItemCOM[22].title = _loc1_.m_cmd;
         this.ItemCOM[22].index = this.ITEM_COM_SUPORT_ACTION;
         this.ItemCOM[23] = new Object();
         this.ItemCOM[23].plate = this.PLATE_TYPE_RESET;
         this.ItemCOM[23].help = String(ExternalInterface.call("MessageConvert","practice_scrFontComReset"));
         _loc1_ = MessageParam(ExternalInterface.call("MessageConvertParam","practice_resetCom"));
         this.ItemCOM[23].title = _loc1_.m_cmd;
         this.ItemCOM[23].index = this.ITEM_COM_RESET;
      }
   }
}

