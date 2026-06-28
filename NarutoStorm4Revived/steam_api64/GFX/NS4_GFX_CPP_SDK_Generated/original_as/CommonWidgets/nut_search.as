package script.net_search
{
   import Enum.Enum_NetLabel;
   import Enum.Enum_NetLabelPlatfrom;
   import InputPad.InputPadKeyCode;
   import KeyHelp.KeyHelpCode;
   import Select.UiSelect;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.*;
   import script.net_card.nut_card;
   import script.net_result.nut_rsult_p;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol16")]
   public class nut_search extends MovieClip
   {
      
      internal static const CCD_UI_NET_SESSIONSELECT_MEMBER_NUM:Number = 8;
      
      public static const CCD_UI_NET_TOPOGRAPHY_ANY:Number = 0;
      
      public static const CCD_UI_NET_TOPOGRAPHY_OFF:Number = 1;
      
      public static const CCD_UI_NET_TOPOGRAPHY_ON:Number = 2;
      
      public static const CCD_UI_NET_ROUND_ANY:Number = 0;
      
      public static const CCD_UI_NET_ROUND_1:Number = 1;
      
      public static const CCD_UI_NET_ROUND_3:Number = 2;
      
      public static const CCD_MATCH_TYPE_RANK:int = 0;
      
      public static const CCD_MATCH_TYPE_PLAYER:int = 1;
      
      public static const CCD_MATCH_TYPE_LEAGUE:int = 2;
      
      public static const CCD_MATCH_TYPE_TOURNAMENT:int = 3;
      
      public static const CCD_MATCH_TYPE_ENDLESS:int = 4;
      
      public var all_card:nut_card;
      
      public var all_listbar00:nut_listbar;
      
      public var all_listbar01:nut_listbar;
      
      public var all_listbar02:nut_listbar;
      
      public var all_rsult_p:nut_rsult_p;
      
      public var all_rule:nut_rule;
      
      public var CallSetStepEnd:Function;
      
      public var CallSetResearch:Function;
      
      public var CallSelectNo:Function;
      
      public var CallSelectOk:Function;
      
      public var CallSetCancel:Function;
      
      public var CallUserCall:Function;
      
      private var m_keyHelp:KeyHelpCode;
      
      internal var m_listMc:Array = new Array();
      
      internal var m_listUse:Array = new Array(CCD_UI_NET_SESSIONSELECT_MEMBER_NUM);
      
      internal var m_listNo:Array = new Array(CCD_UI_NET_SESSIONSELECT_MEMBER_NUM);
      
      internal var m_session_num:int = 8;
      
      internal var m_title_on:Boolean = false;
      
      internal var _pos_bar_start_x:Number = 0;
      
      internal var _pos_bar_start_y:Number = 0;
      
      internal var _pos_bar_space_x:Number = 0;
      
      internal var _pos_bar_space_y:Number = 0;
      
      internal var side:int = 0;
      
      private var m_inputPad:InputPadKeyCode;
      
      private var m_select1:UiSelect;
      
      private var m_select2:UiSelect;
      
      internal var selItem1:Number = 0;
      
      internal var selItem1ValueMax:Number = 0;
      
      internal var selItemSave1:Number = -1;
      
      private var m_member_num:Number = 0;
      
      private var m_check_num:Number = -1;
      
      private var m_flag_animation:Boolean = false;
      
      private var m_flag_endstart:Boolean = false;
      
      private var m_flag_endAnmstart:Boolean = false;
      
      private var m_flag_end:Boolean = false;
      
      private var m_flag_lock:Boolean = false;
      
      private var m_flag_reserch:Boolean = false;
      
      private var m_plat:int = 0;
      
      internal var keypush:Boolean = false;
      
      internal var rule_init:Boolean = false;
      
      public function nut_search()
      {
         super();
         addFrameScript(6,this.frame7,12,this.frame13);
         var _loc1_:Number = 0;
         this.m_keyHelp = new KeyHelpCode();
         this.all_listbar00.visible = false;
         this.all_listbar01.visible = false;
         this.all_listbar02.visible = false;
         this.m_inputPad = new InputPadKeyCode();
         this.m_select1 = new UiSelect();
         this.m_select1.InitSelect(0,0,2,this.m_inputPad.GetKeyInputBtn_L_Up(),this.m_inputPad.GetKeyInputBtn_L_Down(),UiSelect.CCD_LOOP_TYPE_DISABLE);
         this.m_select1.SetEnablePad(this.side);
         this.m_select1.SetDisablePad(1 - this.side);
         _loc1_ = 0;
         while(_loc1_ < this.m_session_num)
         {
            this.m_listUse[_loc1_] = false;
            this.m_listNo[_loc1_] = -1;
            _loc1_++;
         }
         this.all_rsult_p.visible = false;
         this.all_rule.visible = false;
         this.stop();
      }
      
      public function Initialize(param1:Boolean, param2:Function, param3:Function, param4:Function, param5:Function, param6:Function, param7:Function, param8:int, param9:int) : *
      {
         this.m_title_on = param1;
         this.m_plat = param8;
         if(param9 == false)
         {
            this.all_card.visible = false;
         }
         this._pos_bar_start_x = this.all_listbar00.x;
         this._pos_bar_start_y = this.all_listbar00.y;
         param1 = false;
         if(param1)
         {
            this._pos_bar_space_x = this.all_listbar01.x - this.all_listbar00.x;
            this._pos_bar_space_y = this.all_listbar01.y - this.all_listbar00.y;
            this.m_session_num = 8;
         }
         else
         {
            this._pos_bar_space_x = this.all_listbar02.x - this.all_listbar00.x;
            this._pos_bar_space_y = this.all_listbar02.y - this.all_listbar00.y;
            this.m_session_num = 6;
         }
         removeChild(this.all_listbar00);
         removeChild(this.all_listbar01);
         removeChild(this.all_listbar02);
         var _loc10_:Number = 0;
         if(param2 != null)
         {
            this.CallSetStepEnd = param2;
         }
         if(param3 != null)
         {
            this.CallSelectNo = param3;
         }
         if(param4 != null)
         {
            this.CallSelectOk = param4;
         }
         if(param5 != null)
         {
            this.CallSetResearch = param5;
         }
         if(param6 != null)
         {
            this.CallSetCancel = param6;
         }
         if(param7 != null)
         {
            this.CallUserCall = param7;
         }
         var _loc11_:Number = this._pos_bar_start_x;
         var _loc12_:Number = this._pos_bar_start_y;
         _loc10_ = 0;
         while(_loc10_ < this.m_session_num)
         {
            this.m_listMc.push(this.CreateMember(_loc11_,_loc12_,_loc10_));
            _loc11_ += this._pos_bar_space_x;
            _loc12_ += this._pos_bar_space_y;
            _loc10_++;
         }
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
         this.MenuKeyHelp();
      }
      
      public function MenuKeyHelp() : void
      {
         if(this.keypush == true)
         {
            this.m_keyHelp.PopKeyHelp();
            this.keypush = false;
         }
         if(this.m_plat == Enum_NetLabelPlatfrom.CCD_UI_NET_TYPE_PLATFORM_PS4)
         {
            this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_R_UP,"networkmode_575");
         }
         else if(this.m_plat == Enum_NetLabelPlatfrom.CCD_UI_NET_TYPE_PLATFORM_XBOXONE)
         {
            this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_R_UP,"networkmode_576");
         }
         this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_L1,"networkmode_049");
         this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
         this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
         this.m_keyHelp.PushKeyHelp();
         this.keypush = true;
      }
      
      public function CreateMember(param1:Number, param2:Number, param3:Number) : MovieClip
      {
         trace("#CreateMember" + "  bar_no_" + param3);
         var _loc4_:nut_listbar = new nut_listbar();
         if(this.m_title_on == false)
         {
            _loc4_.mc_room.visible = false;
         }
         _loc4_.name = "bar_no" + param3;
         _loc4_.x = param1;
         _loc4_.y = param2;
         this.addChild(_loc4_);
         _loc4_.stop();
         return _loc4_;
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         var _loc3_:nut_listbar = null;
         var _loc4_:int = 0;
         var _loc5_:int = 0;
         var _loc2_:Number = 0;
         if(this.m_flag_end == true)
         {
            return;
         }
         if(this.m_flag_endAnmstart == true)
         {
            if(this.isEndAnimation() == true)
            {
               this.m_flag_end = true;
               if(this.keypush == true)
               {
                  this.m_keyHelp.PopKeyHelp();
                  this.keypush = false;
               }
               if(this.CallSetStepEnd != null)
               {
                  this.CallSetStepEnd();
               }
            }
            return;
         }
         this.m_flag_animation = false;
         _loc2_ = this.m_member_num;
         while(_loc2_ < this.m_session_num)
         {
            if(this.m_listUse[_loc2_] == true)
            {
               _loc3_ = this.m_listMc[_loc2_];
               if(_loc3_.currentFrameLabel != "loop")
               {
                  this.m_flag_animation = true;
                  break;
               }
               if(_loc2_ > this.m_check_num)
               {
                  this.m_check_num = _loc2_;
                  this.m_member_num = this.m_check_num + 1;
                  this.m_select1.SetMinValue(0);
                  this.m_select1.SetMaxValue(this.m_check_num);
               }
            }
            _loc2_++;
         }
         if(this.m_flag_lock == true)
         {
            return;
         }
         if(this.m_member_num > 0 && this.m_flag_endstart == false && this.m_flag_animation == false)
         {
            this.m_select1.SelectMenuCtrl();
            this.selItem1 = this.m_select1.GetSelValue();
            if(this.selItemSave1 != this.selItem1)
            {
               ExternalInterface.call("RequestPlaySE_Select");
               _loc2_ = 0;
               while(_loc2_ < this.m_member_num)
               {
                  _loc3_ = this.m_listMc[_loc2_];
                  if(_loc3_ != null)
                  {
                     if(_loc2_ == this.selItem1)
                     {
                        _loc3_.mc_listbar.gotoAndStop("on_1");
                        _loc3_.mc_room.gotoAndStop("on");
                     }
                     else
                     {
                        _loc3_.mc_listbar.gotoAndStop("off");
                        _loc3_.mc_room.gotoAndStop("off");
                     }
                  }
                  _loc2_++;
               }
               this.selItemSave1 = this.selItem1;
               if(this.CallSelectNo != null)
               {
                  _loc4_ = this.selItemSave1;
                  this.CallSelectNo(_loc4_);
               }
            }
            if(this.m_inputPad.GetKeyInputBtn_Ok() == this.m_inputPad.GetPadPress())
            {
               ExternalInterface.call("PopScrollHelp");
               ExternalInterface.call("RequestPlaySE_Fix");
               this.gotoAndPlay("out");
               this.m_flag_lock = true;
               _loc5_ = this.selItemSave1;
               this.CallSelectOk(_loc5_);
               this.m_flag_endstart = true;
            }
            else if(this.m_inputPad.GetKeyInputBtn_Cancel() == this.m_inputPad.GetPadPress())
            {
               ExternalInterface.call("PopScrollHelp");
               ExternalInterface.call("RequestPlaySE_Cancel");
               this.gotoAndPlay("out");
               this.m_flag_lock = true;
               this.CallSelectOk(-1);
               this.CallSetCancel();
               this.m_flag_endstart = true;
            }
            else if(this.m_inputPad.GetKeyInputBtn_L1() == this.m_inputPad.GetPadPress())
            {
               ExternalInterface.call("PopScrollHelp");
               this.gotoAndPlay("out");
               ExternalInterface.call("RequestPlaySE_Select");
               this.m_flag_reserch = true;
               this.m_flag_lock = true;
               this.CallSelectOk(-1);
               this.CallSetResearch();
               this.m_flag_endstart = true;
            }
            else if(this.m_inputPad.GetKeyInputBtn_R_Up() == this.m_inputPad.GetPadPress())
            {
               this.CallUserCall();
            }
         }
         if(this.m_flag_endstart == true && this.m_flag_animation == false && this.m_flag_endAnmstart == false)
         {
            this.m_flag_endAnmstart = true;
            _loc2_ = 0;
            while(_loc2_ < this.m_member_num)
            {
               _loc3_ = this.m_listMc[_loc2_];
               if(this.m_listUse[_loc2_] == true)
               {
                  if(_loc3_ != null)
                  {
                     _loc3_.gotoAndPlay("out");
                  }
               }
               _loc2_++;
            }
         }
      }
      
      public function isEndAnimation() : Boolean
      {
         var _loc2_:nut_listbar = null;
         var _loc1_:Number = 0;
         _loc1_ = 0;
         while(_loc1_ < this.m_member_num)
         {
            if(this.m_listUse[_loc1_] == true)
            {
               _loc2_ = this.m_listMc[_loc1_];
               if(_loc2_.currentFrameLabel != "end")
               {
                  return false;
               }
            }
            _loc1_++;
         }
         return true;
      }
      
      public function AddUserInfo(param1:Number, param2:String, param3:Number, param4:String, param5:Number, param6:Number, param7:Number, param8:Number, param9:Number, param10:Boolean, param11:int) : void
      {
         var _loc15_:int = 0;
         var _loc16_:String = null;
         var _loc17_:String = null;
         if(this.m_flag_endstart == true)
         {
            return;
         }
         var _loc12_:Number = 0;
         var _loc13_:Number = -1;
         _loc12_ = 0;
         while(_loc12_ < this.m_session_num)
         {
            if(this.m_listUse[_loc12_] == false)
            {
               this.m_listUse[_loc12_] = true;
               _loc13_ = _loc12_;
               break;
            }
            _loc12_++;
         }
         if(_loc13_ < 0)
         {
            return;
         }
         var _loc14_:nut_listbar = this.m_listMc[_loc13_];
         if(_loc14_ != null)
         {
            if(this.m_title_on && param2 != null)
            {
               _loc14_.mc_room.txt_room.SetText(String(ExternalInterface.call("MessageConvert",param2)));
            }
            _loc14_.mc_listbar.all_icon_wave.gotoAndStop("unknown");
            this.SetSessionRtt(_loc13_,param3);
            trace("AddUserInfo Username:" + param4);
            _loc14_.mc_listbar.txt_useid.SetText(param4);
            switch(param5)
            {
               case Enum_NetLabel.CCD_UI_NET_BATTLE_TYPE_ANY:
                  _loc14_.mc_listbar.all_type.visible = false;
                  break;
               case Enum_NetLabel.CCD_UI_NET_BATTLE_TYPE_SINGLE:
                  _loc14_.mc_listbar.all_type.visible = true;
                  _loc14_.mc_listbar.all_type.gotoAndStop("single_m");
                  break;
               case Enum_NetLabel.CCD_UI_NET_BATTLE_TYPE_TEAM:
                  _loc14_.mc_listbar.all_type.visible = true;
                  _loc14_.mc_listbar.all_type.gotoAndStop("team_m");
            }
            _loc15_ = 1;
            if(param6 == CCD_UI_NET_ROUND_3)
            {
               _loc15_ = 3;
            }
            switch(param6)
            {
               case CCD_UI_NET_ROUND_ANY:
                  _loc14_.mc_listbar.all_info.visible = false;
                  break;
               case CCD_UI_NET_ROUND_1:
                  _loc14_.mc_listbar.all_info.visible = true;
                  _loc14_.mc_listbar.all_info.gotoAndStop("round");
                  _loc14_.mc_listbar.all_info.txt_round.SetText(_loc15_);
                  break;
               case CCD_UI_NET_ROUND_3:
                  _loc14_.mc_listbar.all_info.visible = true;
                  _loc14_.mc_listbar.all_info.gotoAndStop("round");
                  _loc14_.mc_listbar.all_info.txt_round.SetText(_loc15_);
            }
            switch(param7)
            {
               case CCD_UI_NET_TOPOGRAPHY_ANY:
                  _loc14_.mc_listbar.all_stage.visible = false;
                  break;
               case CCD_UI_NET_TOPOGRAPHY_OFF:
                  _loc14_.mc_listbar.all_stage.visible = true;
                  _loc14_.mc_listbar.all_stage.gotoAndStop("stage_off");
                  break;
               case CCD_UI_NET_TOPOGRAPHY_ON:
                  _loc14_.mc_listbar.all_stage.visible = true;
                  _loc14_.mc_listbar.all_stage.gotoAndStop("stage_on");
            }
            if(param8 > 0 && param9 > 0)
            {
               _loc14_.mc_listbar.txt_match.SetText("" + param8 + "/" + param9);
            }
            else
            {
               _loc14_.mc_listbar.txt_match.visible = false;
            }
            _loc14_.mc_listbar.all_side.visible = false;
            if(param11 == CCD_MATCH_TYPE_LEAGUE || param11 == CCD_MATCH_TYPE_TOURNAMENT)
            {
               _loc17_ = "alone";
               if(param10 == true)
               {
                  _loc17_ = "side";
               }
               _loc14_.mc_listbar.all_side.visible = true;
               _loc14_.mc_listbar.all_side.gotoAndStop(_loc17_);
            }
            _loc16_ = "p_btl";
            switch(param11)
            {
               case CCD_MATCH_TYPE_LEAGUE:
                  _loc16_ = "leag";
                  break;
               case CCD_MATCH_TYPE_ENDLESS:
                  _loc16_ = "endles";
                  break;
               case CCD_MATCH_TYPE_RANK:
                  _loc16_ = "rank_m";
                  break;
               case CCD_MATCH_TYPE_TOURNAMENT:
                  _loc16_ = "tonmt";
            }
            _loc14_.mc_listbar.all_status.visible = true;
            _loc14_.mc_listbar.all_status.gotoAndStop(_loc16_);
            _loc14_.mc_listbar.gotoAndStop("off");
            _loc14_.gotoAndPlay("in");
         }
         else
         {
            trace("[error] nut_search AddUserInfo mc:" + _loc14_);
         }
      }
      
      public function SetSessionRtt(param1:Number, param2:Number) : void
      {
         if(this.m_flag_endstart == true)
         {
            return;
         }
         var _loc3_:nut_listbar = this.m_listMc[param1];
         if(_loc3_ != null)
         {
            if(param2 == Enum_NetLabel.CCD_UI_NET_RESULT_PLATE_WAVE_UNKNOWN)
            {
               _loc3_.mc_listbar.all_icon_wave.gotoAndStop("unknown");
            }
            else if(param2 == Enum_NetLabel.CCD_UI_NET_RESULT_PLATE_WAVE_NO)
            {
               _loc3_.mc_listbar.all_icon_wave.gotoAndStop("level_0");
            }
            else if(param2 > 0 && param2 <= 3)
            {
               _loc3_.mc_listbar.all_icon_wave.gotoAndStop("level_" + param2);
            }
            else
            {
               _loc3_.mc_listbar.all_icon_wave.gotoAndStop("unknown");
            }
         }
      }
      
      public function SetSessionRule(param1:Boolean, param2:Boolean, param3:Boolean, param4:Boolean) : void
      {
         if(this.m_flag_endstart == true)
         {
            return;
         }
         if(this.rule_init == false)
         {
            this.rule_init = true;
            this.gotoAndPlay("in");
         }
         if(param1 == false)
         {
            this.all_rule.visible = false;
            this.all_rule.txt_rule.visible = false;
            return;
         }
         this.all_rsult_p.visible = true;
         this.all_rule.visible = true;
         var _loc5_:String = "";
         if(param2)
         {
            _loc5_ += String(ExternalInterface.call("MessageConvert","network_sys_022"));
         }
         else
         {
            _loc5_ += String(ExternalInterface.call("MessageConvert","network_sys_024"));
         }
         if(param3)
         {
            _loc5_ += " / ";
            if(param4)
            {
               _loc5_ += String(ExternalInterface.call("MessageConvert","network_sys_014"));
            }
            else
            {
               _loc5_ += String(ExternalInterface.call("MessageConvert","network_sys_015"));
            }
         }
         trace("######## drawtext : " + _loc5_);
         this.all_rule.txt_rule.SetText(_loc5_);
      }
      
      public function setall_card() : void
      {
      }
      
      public function setUnLock() : void
      {
         this.m_flag_lock = false;
      }
      
      public function setEnd() : void
      {
         this.m_flag_endstart = true;
      }
      
      internal function frame7() : *
      {
         stop();
      }
      
      internal function frame13() : *
      {
         stop();
      }
   }
}

