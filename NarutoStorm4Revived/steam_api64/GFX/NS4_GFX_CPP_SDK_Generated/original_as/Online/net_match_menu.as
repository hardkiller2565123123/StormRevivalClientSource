package script.net_match_1
{
   import Enum.Enum_NetLabel;
   import Enum.Enum_NetLabelPlatfrom;
   import InputPad.InputPadKeyCode;
   import KeyHelp.KeyHelpCode;
   import Select.UiSelect;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.*;
   
   public class net_match_menu extends MovieClip
   {
      
      internal static const CCD_UI_NET_LOBBY_MENU_ON:Number = 0;
      
      internal static const CCD_UI_NET_LOBBY_MENU_OFF:Number = 1;
      
      internal static const CCD_UI_NET_LOBBY_MENU_NONE_ON:Number = 2;
      
      internal static const CCD_UI_NET_LOBBY_MENU_NONE_OFF:Number = 3;
      
      public var SetStepEnd:Function;
      
      public var SelectNo:Function;
      
      public var MessageCall:Function;
      
      public var MatchingVoiceAnmLoop:Function;
      
      public var MatchingVoiceAnmOut:Function;
      
      internal var m_listMc:Array = new Array();
      
      internal var m_listType:Array = null;
      
      internal var m_listLock:Array = new Array();
      
      internal var m_ok:Boolean = false;
      
      internal var m_init:Boolean = false;
      
      internal var m_end:Boolean = false;
      
      internal var m_anmend:Boolean = false;
      
      internal var m_anmstart:Boolean = false;
      
      internal var m_voice:Boolean = false;
      
      internal var m_type:* = 100;
      
      internal var _pos_bar_start_x:Number = 0;
      
      internal var _pos_bar_start_y:Number = 0;
      
      internal var _pos_bar_space_x:Number = 0;
      
      internal var _pos_bar_space_y:Number = 0;
      
      internal var side:int = 0;
      
      private var m_keyHelp:KeyHelpCode;
      
      private var m_inputPad:InputPadKeyCode;
      
      private var m_select1:UiSelect;
      
      private var m_select2:UiSelect;
      
      internal var selItem1:Number = 0;
      
      internal var selItem1ValueMax:Number = 0;
      
      internal var selItemSave1:Number = -1;
      
      internal var selItemValue:Number = -1;
      
      internal var m_lock:Boolean = false;
      
      internal var m_onUser:Boolean = false;
      
      internal var m_host:Boolean = false;
      
      internal var m_lockOk:Boolean = false;
      
      internal var m_lockKick:Boolean = false;
      
      internal var m_waitOk:Boolean = false;
      
      internal var m_user_select:Boolean = false;
      
      internal var m_MatchingVoiceStep:int = 0;
      
      internal var m_platfrom:int = 0;
      
      internal var m_usernum:int = 0;
      
      internal var m_usernum_max:int = 8;
      
      internal var keypush:Boolean = false;
      
      internal var m_ScrollHelp_log:int = -1;
      
      internal var m_ScrollHelp_set:int = -1;
      
      public function net_match_menu()
      {
         super();
      }
      
      public function start(param1:Class, param2:Number, param3:int) : void
      {
         var _loc4_:Number = 0;
         var _loc5_:MovieClip = null;
         var _loc6_:MovieClip = null;
         this.m_platfrom = param3;
         this.m_keyHelp = new KeyHelpCode();
         ExternalInterface.call("PushScrollHelp");
         this.m_type = param2;
         _loc5_ = this.getChildByName("all_menu00") as MovieClip;
         if(_loc5_)
         {
            this._pos_bar_start_x = _loc5_.x;
            this._pos_bar_start_y = _loc5_.y;
         }
         else
         {
            trace("# net_match_menu  all_menu00 null ");
         }
         _loc6_ = this.getChildByName("all_menu01") as MovieClip;
         if(_loc6_)
         {
            if(_loc5_)
            {
               this._pos_bar_space_x = _loc6_.x - _loc5_.x;
               this._pos_bar_space_y = _loc6_.y - _loc5_.y;
            }
         }
         else
         {
            trace("# net_match_menu  all_menu01 null ");
         }
         this.m_inputPad = new InputPadKeyCode();
         this.m_select1 = new UiSelect();
         this.m_select1.InitSelect(0,0,2,this.m_inputPad.GetKeyInputBtn_L_Up(),this.m_inputPad.GetKeyInputBtn_L_Down(),UiSelect.CCD_LOOP_TYPE_DISABLE);
         this.m_select1.SetEnablePad(this.side);
         this.m_select1.SetDisablePad(1 - this.side);
         this.m_select1.SetLoopType(UiSelect.CCD_LOOP_TYPE_PUSH);
         if(this.m_listType)
         {
            this.m_listType = null;
         }
         this.m_listType = this.getMenuList(this.m_type);
         var _loc7_:Number = this._pos_bar_start_x;
         var _loc8_:Number = this._pos_bar_start_y;
         var _loc9_:MovieClip = null;
         _loc9_ = this.getChildByName("all_menu00") as MovieClip;
         _loc9_.visible = false;
         _loc9_ = this.getChildByName("all_menu01") as MovieClip;
         _loc9_.visible = false;
         _loc9_ = this.getChildByName("all_menu02") as MovieClip;
         _loc9_.visible = false;
         _loc9_ = this.getChildByName("all_menu03") as MovieClip;
         _loc9_.visible = false;
         _loc9_ = this.getChildByName("all_menu04") as MovieClip;
         _loc9_.visible = false;
         _loc9_ = this.getChildByName("all_menu05") as MovieClip;
         _loc9_.visible = false;
         _loc9_ = this.getChildByName("all_menu06") as MovieClip;
         _loc9_.visible = false;
         _loc9_ = this.getChildByName("all_menu07") as MovieClip;
         _loc9_.visible = false;
         _loc4_ = 0;
         while(_loc4_ < this.m_listType.length)
         {
            this.m_listMc.push(this.createMenu(_loc4_,param1,this.m_listType[_loc4_],_loc7_,_loc8_));
            this.m_listLock.push(false);
            _loc7_ += this._pos_bar_space_x;
            _loc8_ += this._pos_bar_space_y;
            _loc4_++;
         }
         this.m_select1.SetMinValue(0);
         this.m_select1.SetMaxValue(this.m_listType.length - 1);
         this.m_select1.SetSelValue(0);
         this.setOnUser(this.m_onUser);
         switch(this.m_type)
         {
            case Enum_NetLabel.CCD_UI_NET_TYPE_RANK:
            case Enum_NetLabel.CCD_UI_NET_TYPE_PLAYER:
               _loc5_ = this.getChildByName("all_match_p1") as MovieClip;
               _loc6_ = this.getChildByName("all_match_p2") as MovieClip;
               if(_loc5_)
               {
                  _loc5_.all_icon_player_m.gotoAndStop("1p");
               }
               else
               {
                  trace("# net_match_menu  all_match_p1 null ");
               }
               if(_loc6_)
               {
                  _loc6_.all_icon_player_m.gotoAndStop("2p");
               }
               else
               {
                  trace("# net_match_menu  all_match_p2 null ");
               }
         }
         this.menu(0);
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
         this.stop();
      }
      
      public function Finalize() : void
      {
         trace("## net_menu Finalize 1");
         removeEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
         ExternalInterface.call("PopScrollHelp");
         if(this.keypush == true && Boolean(this.m_keyHelp))
         {
            trace("## net_menu Finalize 2");
            this.m_keyHelp.PopKeyHelp();
            this.keypush = false;
         }
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         var _loc7_:MovieClip = null;
         var _loc8_:int = 0;
         var _loc9_:* = undefined;
         var _loc2_:Number = 0;
         var _loc3_:MovieClip = null;
         var _loc4_:MovieClip = null;
         if(this.m_end == true)
         {
            this.SetStepEnd();
            removeEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
            return;
         }
         switch(this.m_type)
         {
            case Enum_NetLabel.CCD_UI_NET_TYPE_RANK:
            case Enum_NetLabel.CCD_UI_NET_TYPE_PLAYER:
               _loc7_ = this.getChildByName("mc_voice") as MovieClip;
               switch(this.m_MatchingVoiceStep)
               {
                  case 0:
                     break;
                  case 1:
                     if(_loc7_.currentFrameLabel == "loop")
                     {
                        this.MatchingVoiceAnmLoop();
                        this.m_MatchingVoiceStep = 0;
                     }
                     break;
                  case 2:
                     if(_loc7_.currentFrameLabel == "end")
                     {
                        this.MatchingVoiceAnmOut();
                        this.m_MatchingVoiceStep = 0;
                     }
               }
         }
         if(this.m_anmend == true)
         {
            switch(this.m_type)
            {
               case Enum_NetLabel.CCD_UI_NET_TYPE_RANK:
               case Enum_NetLabel.CCD_UI_NET_TYPE_PLAYER:
                  _loc4_ = this.getChildByName("all_vs_l") as MovieClip;
                  _loc4_.visible = false;
                  break;
               case Enum_NetLabel.CCD_UI_NET_TYPE_ENDLESS:
               case Enum_NetLabel.CCD_UI_NET_TYPE_LEAGUE:
               case Enum_NetLabel.CCD_UI_NET_TYPE_TOURNAMENT:
            }
            if(this.currentFrame == this.totalFrames)
            {
               this.m_end = true;
            }
            return;
         }
         if(this.m_anmstart == true)
         {
            if(this.currentFrameLabel == "loop")
            {
               this.m_anmstart = false;
            }
            return;
         }
         if(this.m_lock == true)
         {
            return;
         }
         this.m_select1.SelectMenuCtrl();
         this.selItem1 = this.m_select1.GetSelValue();
         if(this.selItemSave1 != this.selItem1)
         {
            ExternalInterface.call("RequestPlaySE_Select");
            this.menu(this.selItem1);
            this.selItemValue = this.m_listType[this.selItem1];
            this.setMenuKeyHelp(this.selItemValue);
            this.setMenuTextScrollHelp(this.selItemValue);
            this.selItemSave1 = this.selItem1;
            if(this.SelectNo != null)
            {
               _loc8_ = this.selItemSave1;
               this.SelectNo(_loc8_);
            }
         }
         var _loc5_:int;
         var _loc6_:int = _loc5_ = int(this.m_listType[this.selItem1]);
         if(this.m_inputPad.GetKeyInputBtn_Ok() == this.m_inputPad.GetPadPress())
         {
            _loc9_ = true;
            if(this.m_listLock[this.selItem1] == false)
            {
               if(!(this.m_lockKick == true && _loc5_ == Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK))
               {
                  if(!(this.m_lockOk == true && _loc5_ == Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK))
                  {
                     _loc9_ = true;
                     switch(_loc5_)
                     {
                        case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK:
                           if(this.keypush == true)
                           {
                              this.m_keyHelp.PopKeyHelp();
                              this.keypush = false;
                           }
                           this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_CANCEL);
                           this.m_keyHelp.PushKeyHelp();
                           this.keypush = true;
                           ExternalInterface.call("SetScrollHelpId","MSG_WaitMoment");
                           this.m_lock = true;
                           break;
                        case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_PROFILE:
                        case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_RECODE:
                        case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK:
                           switch(this.m_type)
                           {
                              case Enum_NetLabel.CCD_UI_NET_TYPE_RANK:
                              case Enum_NetLabel.CCD_UI_NET_TYPE_PLAYER:
                                 break;
                              case Enum_NetLabel.CCD_UI_NET_TYPE_ENDLESS:
                              case Enum_NetLabel.CCD_UI_NET_TYPE_LEAGUE:
                              case Enum_NetLabel.CCD_UI_NET_TYPE_TOURNAMENT:
                                 _loc9_ = false;
                                 this.m_lock = true;
                                 this.m_user_select = true;
                           }
                        case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FRIEND:
                        case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_OUT:
                        case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VOICECHAT:
                     }
                  }
               }
            }
            else
            {
               _loc9_ = false;
               switch(_loc5_)
               {
                  case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK:
                     break;
                  case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_PROFILE:
                  case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_RECODE:
                  case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK:
                     switch(this.m_type)
                     {
                        case Enum_NetLabel.CCD_UI_NET_TYPE_RANK:
                        case Enum_NetLabel.CCD_UI_NET_TYPE_PLAYER:
                        case Enum_NetLabel.CCD_UI_NET_TYPE_ENDLESS:
                        case Enum_NetLabel.CCD_UI_NET_TYPE_LEAGUE:
                        case Enum_NetLabel.CCD_UI_NET_TYPE_TOURNAMENT:
                     }
                  case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FRIEND:
                  case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_OUT:
                  case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VOICECHAT:
               }
            }
            if(this.m_lockKick && _loc5_ == Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK)
            {
               _loc9_ = false;
            }
            if(this.m_lockOk && _loc5_ == Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK)
            {
               _loc9_ = false;
            }
            if(this.MessageCall != null && _loc9_ == true)
            {
               ExternalInterface.call("RequestPlaySE_Fix");
               this.MessageCall(_loc6_);
            }
            else
            {
               ExternalInterface.call("RequestPlaySE_Fix");
            }
         }
      }
      
      public function createMenu(param1:Number, param2:Class, param3:Number, param4:Number, param5:Number) : MovieClip
      {
         var _loc6_:MovieClip = null;
         if(param1 == 0)
         {
            _loc6_ = this.getChildByName("all_menu00") as MovieClip;
         }
         if(param1 == 1)
         {
            _loc6_ = this.getChildByName("all_menu01") as MovieClip;
         }
         if(param1 == 2)
         {
            _loc6_ = this.getChildByName("all_menu02") as MovieClip;
         }
         if(param1 == 3)
         {
            _loc6_ = this.getChildByName("all_menu03") as MovieClip;
         }
         if(param1 == 4)
         {
            _loc6_ = this.getChildByName("all_menu04") as MovieClip;
         }
         if(param1 == 5)
         {
            _loc6_ = this.getChildByName("all_menu05") as MovieClip;
         }
         if(param1 == 6)
         {
            _loc6_ = this.getChildByName("all_menu06") as MovieClip;
         }
         if(param1 == 7)
         {
            _loc6_ = this.getChildByName("all_menu07") as MovieClip;
         }
         _loc6_.visible = true;
         this.setMenuText(_loc6_,param3);
         return _loc6_;
      }
      
      public function menu(param1:Number) : void
      {
         var _loc2_:Number = 0;
         var _loc3_:MovieClip = null;
         _loc2_ = 0;
         while(_loc2_ < this.m_listType.length)
         {
            _loc3_ = this.m_listMc[_loc2_];
            if(_loc3_ != null)
            {
               if(this.m_listLock[_loc2_] == true)
               {
                  if(_loc2_ == param1)
                  {
                     this.setMenuState(_loc3_,CCD_UI_NET_LOBBY_MENU_NONE_ON);
                  }
                  else
                  {
                     this.setMenuState(_loc3_,CCD_UI_NET_LOBBY_MENU_NONE_OFF);
                  }
               }
               else if(this.m_listType[_loc2_] == Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK && this.m_lockKick == true)
               {
                  if(_loc2_ == param1)
                  {
                     this.setMenuState(_loc3_,CCD_UI_NET_LOBBY_MENU_NONE_ON);
                  }
                  else
                  {
                     this.setMenuState(_loc3_,CCD_UI_NET_LOBBY_MENU_NONE_OFF);
                  }
               }
               else if(this.m_listType[_loc2_] == Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK && this.m_lockOk == true)
               {
                  if(_loc2_ == param1)
                  {
                     this.setMenuState(_loc3_,CCD_UI_NET_LOBBY_MENU_NONE_ON);
                  }
                  else
                  {
                     this.setMenuState(_loc3_,CCD_UI_NET_LOBBY_MENU_NONE_OFF);
                  }
               }
               else if(_loc2_ == param1)
               {
                  this.setMenuState(_loc3_,CCD_UI_NET_LOBBY_MENU_ON);
               }
               else
               {
                  this.setMenuState(_loc3_,CCD_UI_NET_LOBBY_MENU_OFF);
               }
            }
            _loc2_++;
         }
      }
      
      public function setMenuState(param1:MovieClip, param2:Number) : void
      {
         switch(param2)
         {
            case CCD_UI_NET_LOBBY_MENU_ON:
               param1.gotoAndStop("on");
               break;
            case CCD_UI_NET_LOBBY_MENU_OFF:
               param1.gotoAndStop("off");
               break;
            case CCD_UI_NET_LOBBY_MENU_NONE_ON:
               param1.gotoAndStop("none_on");
               break;
            case CCD_UI_NET_LOBBY_MENU_NONE_OFF:
               param1.gotoAndStop("none_off");
         }
      }
      
      public function getMenuList(param1:Number) : Array
      {
         var _loc2_:Array = new Array();
         switch(param1)
         {
            case Enum_NetLabel.CCD_UI_NET_TYPE_RANK:
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_RECODE);
               if(this.m_platfrom != Enum_NetLabelPlatfrom.CCD_UI_NET_TYPE_PLATFORM_PC)
               {
                  _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_PROFILE);
               }
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FREEBATTLE);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_OUT);
               break;
            case Enum_NetLabel.CCD_UI_NET_TYPE_PLAYER:
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_RECODE);
               if(this.m_platfrom != Enum_NetLabelPlatfrom.CCD_UI_NET_TYPE_PLATFORM_PC)
               {
                  _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_PROFILE);
               }
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FRIEND);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FREEBATTLE);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_OUT);
               break;
            case Enum_NetLabel.CCD_UI_NET_TYPE_ENDLESS:
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_RECODE);
               if(this.m_platfrom != Enum_NetLabelPlatfrom.CCD_UI_NET_TYPE_PLATFORM_PC)
               {
                  _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_PROFILE);
               }
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FRIEND);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_OUT);
               break;
            case Enum_NetLabel.CCD_UI_NET_TYPE_LEAGUE:
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_RECODE);
               if(this.m_platfrom != Enum_NetLabelPlatfrom.CCD_UI_NET_TYPE_PLATFORM_PC)
               {
                  _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_PROFILE);
               }
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FRIEND);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_OUT);
               break;
            case Enum_NetLabel.CCD_UI_NET_TYPE_TOURNAMENT:
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_RECODE);
               if(this.m_platfrom != Enum_NetLabelPlatfrom.CCD_UI_NET_TYPE_PLATFORM_PC)
               {
                  _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_PROFILE);
               }
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FRIEND);
               _loc2_.push(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_OUT);
         }
         return _loc2_;
      }
      
      public function setMenuKeyHelp(param1:Number) : void
      {
         trace("# setMenuKeyHelp  ");
         if(this.keypush == true)
         {
            this.m_keyHelp.PopKeyHelp();
            this.keypush = false;
         }
         switch(param1)
         {
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK:
               switch(this.m_type)
               {
                  case Enum_NetLabel.CCD_UI_NET_TYPE_RANK:
                  case Enum_NetLabel.CCD_UI_NET_TYPE_PLAYER:
                     if(this.m_onUser == true)
                     {
                        this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
                     }
                     this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
                     this.m_keyHelp.PushKeyHelp();
                     this.keypush = true;
                     break;
                  case Enum_NetLabel.CCD_UI_NET_TYPE_ENDLESS:
                  case Enum_NetLabel.CCD_UI_NET_TYPE_LEAGUE:
                     if(this.m_ok == false)
                     {
                        if(this.m_usernum > 1 && this.m_waitOk == false)
                        {
                           this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
                        }
                        this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
                        this.m_keyHelp.PushKeyHelp();
                        this.keypush = true;
                     }
                     else
                     {
                        this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_CANCEL);
                        this.m_keyHelp.PushKeyHelp();
                        this.keypush = true;
                     }
                     break;
                  case Enum_NetLabel.CCD_UI_NET_TYPE_TOURNAMENT:
                     if(this.m_ok == false)
                     {
                        if(this.m_usernum > 2 && this.m_waitOk == false)
                        {
                           this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
                        }
                        this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
                        this.m_keyHelp.PushKeyHelp();
                        this.keypush = true;
                     }
                     else
                     {
                        this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_CANCEL);
                        this.m_keyHelp.PushKeyHelp();
                        this.keypush = true;
                     }
               }
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_RECODE:
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
               this.m_keyHelp.PushKeyHelp();
               this.keypush = true;
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_PROFILE:
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
               this.m_keyHelp.PushKeyHelp();
               this.keypush = true;
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK:
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
               this.m_keyHelp.PushKeyHelp();
               this.keypush = true;
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FRIEND:
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
               this.m_keyHelp.PushKeyHelp();
               this.keypush = true;
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VOICECHAT:
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
               this.m_keyHelp.PushKeyHelp();
               this.keypush = true;
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_OUT:
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
               this.m_keyHelp.PushKeyHelp();
               this.keypush = true;
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FREEBATTLE:
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
               this.m_keyHelp.PushKeyHelp();
               this.keypush = true;
         }
      }
      
      public function setMenuText(param1:MovieClip, param2:Number) : void
      {
         switch(param2)
         {
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK:
               this.setMenuText_sub(param1,"networkmode_184");
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_RECODE:
               this.setMenuText_sub(param1,"networkmode_574");
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_PROFILE:
               if(this.m_platfrom == Enum_NetLabelPlatfrom.CCD_UI_NET_TYPE_PLATFORM_PS4)
               {
                  this.setMenuText_sub(param1,"networkmode_575");
               }
               else
               {
                  this.setMenuText_sub(param1,"networkmode_576");
               }
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK:
               this.setMenuText_sub(param1,"network_sys_004");
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FRIEND:
               this.setMenuText_sub(param1,"networkmode_150");
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VOICECHAT:
               if(this.m_voice)
               {
                  this.setMenuText_sub(param1,"networkmode_578");
               }
               else
               {
                  this.setMenuText_sub(param1,"networkmode_579");
               }
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_OUT:
               this.setMenuText_sub(param1,"networkmode_187");
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FREEBATTLE:
               this.setMenuText_sub(param1,"networkmode_580");
         }
      }
      
      public function setMenuTextScrollHelp(param1:Number) : void
      {
         if(param1 != Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK)
         {
            this.m_ScrollHelp_log = -1;
         }
         switch(param1)
         {
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK:
               switch(this.m_type)
               {
                  case Enum_NetLabel.CCD_UI_NET_TYPE_RANK:
                  case Enum_NetLabel.CCD_UI_NET_TYPE_PLAYER:
                     if(this.m_onUser == true)
                     {
                        this.m_ScrollHelp_set = 0;
                     }
                     else
                     {
                        this.m_ScrollHelp_set = 1;
                     }
                     if(this.m_ScrollHelp_set != this.m_ScrollHelp_log)
                     {
                        this.m_ScrollHelp_log = this.m_ScrollHelp_set;
                        if(this.m_ScrollHelp_set == 0)
                        {
                           ExternalInterface.call("SetScrollHelpId","networkmode_192");
                        }
                        else
                        {
                           ExternalInterface.call("SetScrollHelpId","networkmode_259");
                        }
                     }
                     break;
                  case Enum_NetLabel.CCD_UI_NET_TYPE_ENDLESS:
                     if(this.m_waitOk == true)
                     {
                        this.m_ScrollHelp_set = 3;
                     }
                     else if(this.m_ok == false)
                     {
                        if(this.m_onUser == true)
                        {
                           this.m_ScrollHelp_set = 0;
                        }
                        else
                        {
                           this.m_ScrollHelp_set = 1;
                        }
                     }
                     else
                     {
                        this.m_ScrollHelp_set = 2;
                     }
                     if(this.m_ScrollHelp_set != this.m_ScrollHelp_log)
                     {
                        this.m_ScrollHelp_log = this.m_ScrollHelp_set;
                        if(this.m_ScrollHelp_set == 0)
                        {
                           ExternalInterface.call("SetScrollHelpId","networkmode_192");
                        }
                        else if(this.m_ScrollHelp_set == 1)
                        {
                           ExternalInterface.call("SetScrollHelpId","networkmode_259");
                        }
                        else if(this.m_ScrollHelp_set == 2)
                        {
                           ExternalInterface.call("SetScrollHelpId","MSG_WaitMoment");
                        }
                        else if(this.m_ScrollHelp_set == 3)
                        {
                           ExternalInterface.call("SetScrollHelpId","networkmode_259");
                        }
                     }
                     break;
                  case Enum_NetLabel.CCD_UI_NET_TYPE_LEAGUE:
                     if(this.m_waitOk == true)
                     {
                        this.m_ScrollHelp_set = 3;
                     }
                     else if(this.m_ok == false)
                     {
                        if(this.m_usernum > 1)
                        {
                           this.m_ScrollHelp_set = 0;
                        }
                        else
                        {
                           this.m_ScrollHelp_set = 1;
                        }
                     }
                     else
                     {
                        this.m_ScrollHelp_set = 2;
                     }
                     if(this.m_ScrollHelp_set != this.m_ScrollHelp_log)
                     {
                        this.m_ScrollHelp_log = this.m_ScrollHelp_set;
                        if(this.m_ScrollHelp_set == 0)
                        {
                           ExternalInterface.call("SetScrollHelpId","networkmode_192");
                        }
                        else if(this.m_ScrollHelp_set == 1)
                        {
                           ExternalInterface.call("SetScrollHelpId","networkmode_594");
                        }
                        else if(this.m_ScrollHelp_set == 2)
                        {
                           ExternalInterface.call("SetScrollHelpId","MSG_WaitMoment");
                        }
                        else if(this.m_ScrollHelp_set == 3)
                        {
                           ExternalInterface.call("SetScrollHelpId","networkmode_259");
                        }
                     }
                     break;
                  case Enum_NetLabel.CCD_UI_NET_TYPE_TOURNAMENT:
                     if(this.m_waitOk == true)
                     {
                        this.m_ScrollHelp_set = 3;
                     }
                     else if(this.m_ok == false)
                     {
                        if(this.m_usernum > 2)
                        {
                           this.m_ScrollHelp_set = 0;
                        }
                        else
                        {
                           this.m_ScrollHelp_set = 1;
                        }
                     }
                     else
                     {
                        this.m_ScrollHelp_set = 2;
                     }
                     if(this.m_ScrollHelp_set != this.m_ScrollHelp_log)
                     {
                        this.m_ScrollHelp_log = this.m_ScrollHelp_set;
                        if(this.m_ScrollHelp_set == 0)
                        {
                           ExternalInterface.call("SetScrollHelpId","networkmode_192");
                        }
                        else if(this.m_ScrollHelp_set == 1)
                        {
                           ExternalInterface.call("SetScrollHelpId","network_sys_145");
                        }
                        else if(this.m_ScrollHelp_set == 2)
                        {
                           ExternalInterface.call("SetScrollHelpId","MSG_WaitMoment");
                        }
                        else if(this.m_ScrollHelp_set == 3)
                        {
                           ExternalInterface.call("SetScrollHelpId","networkmode_259");
                        }
                     }
               }
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_RECODE:
               ExternalInterface.call("SetScrollHelpId","networkmode_534");
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_PROFILE:
               if(this.m_platfrom == Enum_NetLabelPlatfrom.CCD_UI_NET_TYPE_PLATFORM_PS4)
               {
                  ExternalInterface.call("SetScrollHelpId","networkmode_581");
               }
               else
               {
                  ExternalInterface.call("SetScrollHelpId","networkmode_582");
               }
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK:
               ExternalInterface.call("SetScrollHelpId","networkmode_194");
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FRIEND:
               ExternalInterface.call("SetScrollHelpId","networkmode_583");
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VOICECHAT:
               if(this.m_voice)
               {
                  ExternalInterface.call("SetScrollHelpId","networkmode_584");
               }
               else
               {
                  ExternalInterface.call("SetScrollHelpId","networkmode_585");
               }
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FREEBATTLE:
               ExternalInterface.call("SetScrollHelpId","networkmode_586");
               break;
            case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_OUT:
               ExternalInterface.call("SetScrollHelpId","networkmode_195");
         }
      }
      
      public function SetVoiceIn() : void
      {
         var _loc1_:MovieClip = this.getChildByName("mc_voice") as MovieClip;
         _loc1_.txt_voice.SetText("");
         _loc1_.visible = true;
         _loc1_.gotoAndPlay("in");
         this.m_MatchingVoiceStep = 1;
      }
      
      public function SetVoiceOut() : void
      {
         var _loc1_:MovieClip = this.getChildByName("mc_voice") as MovieClip;
         _loc1_.txt_voice.SetText("");
         _loc1_.gotoAndPlay("out");
         this.m_MatchingVoiceStep = 2;
      }
      
      public function setStart(param1:Boolean) : void
      {
         this.m_host = param1;
         if(this.m_anmend == true)
         {
            return;
         }
         this.m_anmstart = true;
         this.gotoAndPlay("in");
      }
      
      public function setHost(param1:Boolean) : void
      {
         this.m_host = param1;
      }
      
      public function setEnd() : void
      {
         if(this.m_anmend == true)
         {
            return;
         }
         this.m_anmend = true;
         this.gotoAndPlay("out");
      }
      
      public function setLockOk() : void
      {
         if(this.m_anmend == true)
         {
            return;
         }
         if(this.m_lockOk == false)
         {
            this.m_lockOk = true;
            this.menu(this.m_select1.GetSelValue());
         }
      }
      
      public function setUnLockOk() : void
      {
         if(this.m_anmend == true)
         {
            return;
         }
         if(this.m_lockOk == true)
         {
            this.m_lockOk = false;
            this.menu(this.m_select1.GetSelValue());
         }
      }
      
      public function setLockKick() : void
      {
         if(this.m_anmend == true)
         {
            return;
         }
         if(this.m_lockKick == false)
         {
            this.m_lockKick = true;
            this.menu(this.m_select1.GetSelValue());
         }
      }
      
      public function setUnLockKick() : void
      {
         if(this.m_anmend == true)
         {
            return;
         }
         if(this.m_lockKick == true)
         {
            this.m_lockKick = false;
            this.menu(this.m_select1.GetSelValue());
         }
      }
      
      public function setLock() : Boolean
      {
         this.m_lock = true;
         return true;
      }
      
      public function setCancelLock() : Boolean
      {
         this.setMenuKeyHelp(this.selItemValue);
         this.setMenuTextScrollHelp(this.selItemValue);
         this.m_lock = false;
         return true;
      }
      
      public function setMyVoice(param1:Boolean) : void
      {
         var _loc2_:Number = NaN;
         var _loc3_:MovieClip = null;
         this.m_voice = param1;
         if(this.selItemSave1 >= 0)
         {
            _loc2_ = 0;
            _loc3_ = null;
            _loc2_ = 0;
            while(_loc2_ < this.m_listType.length)
            {
               if(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VOICECHAT == this.m_listType[_loc2_])
               {
                  _loc3_ = this.m_listMc[_loc2_];
                  if(_loc3_ != null)
                  {
                     this.setMenuText(_loc3_,Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VOICECHAT);
                     this.setMenuKeyHelp(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VOICECHAT);
                     this.setMenuTextScrollHelp(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VOICECHAT);
                  }
               }
               _loc2_++;
            }
         }
      }
      
      public function getLock() : Boolean
      {
         return this.m_lock;
      }
      
      public function getSelectValue() : Number
      {
         return this.selItemValue;
      }
      
      public function _getUserSelect() : Boolean
      {
         return this.m_user_select;
      }
      
      public function _setUserSelect(param1:Boolean) : void
      {
         this.m_user_select = param1;
      }
      
      public function setOnUserNum(param1:int, param2:int) : void
      {
         this.m_usernum = param1;
         this.m_usernum_max = param2;
      }
      
      public function setWaitOk(param1:Boolean) : void
      {
         this.m_waitOk = param1;
      }
      
      public function setOnUser(param1:Boolean) : void
      {
         var _loc3_:MovieClip = null;
         if(this.m_anmend == true && this.m_listType == null)
         {
            return;
         }
         var _loc2_:Number = 0;
         this.m_onUser = param1;
         if(this.m_onUser == true)
         {
            _loc2_ = 0;
            for(; _loc2_ < this.m_listType.length; _loc2_++)
            {
               this.m_listLock[_loc2_] = false;
               if(this.m_host == false)
               {
                  switch(this.m_listType[_loc2_])
                  {
                     case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK:
                        this.m_listLock[_loc2_] = true;
                        break;
                     case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FREEBATTLE:
                        this.m_listLock[_loc2_] = true;
                  }
               }
               switch(this.m_type)
               {
                  case Enum_NetLabel.CCD_UI_NET_TYPE_RANK:
                  case Enum_NetLabel.CCD_UI_NET_TYPE_PLAYER:
                     switch(this.m_listType[_loc2_])
                     {
                        case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FRIEND:
                           this.m_listLock[_loc2_] = true;
                           break;
                        case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FREEBATTLE:
                           this.m_listLock[_loc2_] = true;
                     }
                     break;
                  case Enum_NetLabel.CCD_UI_NET_TYPE_ENDLESS:
                  case Enum_NetLabel.CCD_UI_NET_TYPE_LEAGUE:
                  case Enum_NetLabel.CCD_UI_NET_TYPE_TOURNAMENT:
                     if(this.m_usernum >= this.m_usernum_max)
                     {
                        switch(this.m_listType[_loc2_])
                        {
                           case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FRIEND:
                              this.m_listLock[_loc2_] = true;
                        }
                     }
               }
               switch(this.m_type)
               {
                  case Enum_NetLabel.CCD_UI_NET_TYPE_RANK:
                  case Enum_NetLabel.CCD_UI_NET_TYPE_PLAYER:
                     break;
                  case Enum_NetLabel.CCD_UI_NET_TYPE_ENDLESS:
                     if(this.m_waitOk == true)
                     {
                        switch(this.m_listType[_loc2_])
                        {
                           case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK:
                              this.m_listLock[_loc2_] = true;
                        }
                     }
                     break;
                  case Enum_NetLabel.CCD_UI_NET_TYPE_LEAGUE:
                     if(this.m_waitOk == true)
                     {
                        switch(this.m_listType[_loc2_])
                        {
                           case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK:
                              this.m_listLock[_loc2_] = true;
                        }
                     }
                     break;
                  case Enum_NetLabel.CCD_UI_NET_TYPE_TOURNAMENT:
                     if(this.m_waitOk == true)
                     {
                        switch(this.m_listType[_loc2_])
                        {
                           case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK:
                              this.m_listLock[_loc2_] = true;
                        }
                     }
                     if(this.m_usernum <= 2)
                     {
                        switch(this.m_listType[_loc2_])
                        {
                           case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK:
                              this.m_listLock[_loc2_] = true;
                        }
                     }
               }
               if(this.m_host != false)
               {
                  continue;
               }
               switch(this.m_listType[_loc2_])
               {
                  case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FRIEND:
                     this.m_listLock[_loc2_] = true;
               }
            }
         }
         else
         {
            _loc2_ = 0;
            for(; _loc2_ < this.m_listType.length; _loc2_++)
            {
               this.m_listLock[_loc2_] = false;
               switch(this.m_listType[_loc2_])
               {
                  case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK:
                  case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_PROFILE:
                  case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_KICK:
                     this.m_listLock[_loc2_] = true;
               }
               if(this.m_host != false)
               {
                  continue;
               }
               switch(this.m_listType[_loc2_])
               {
                  case Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_FRIEND:
                     this.m_listLock[_loc2_] = true;
               }
            }
         }
         if(this.m_select1)
         {
            this.menu(this.m_select1.GetSelValue());
         }
         if(this.m_lock == false)
         {
            if(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK == this.selItemValue)
            {
               _loc3_ = null;
               _loc2_ = 0;
               while(_loc2_ < this.m_listType.length)
               {
                  if(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK == this.m_listType[_loc2_])
                  {
                     _loc3_ = this.m_listMc[_loc2_];
                     if(_loc3_ != null)
                     {
                        this.setMenuText(_loc3_,Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK);
                        this.setMenuKeyHelp(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK);
                        this.setMenuTextScrollHelp(Enum_NetLabel.CCD_UI_NET_LOBBY_MENU_TYPE_VSOK);
                     }
                  }
                  _loc2_++;
               }
            }
         }
      }
      
      public function setOnOk(param1:Boolean) : void
      {
         this.m_ok = param1;
      }
      
      public function setMenuText_sub(param1:MovieClip, param2:String) : void
      {
         if(param1 != null)
         {
            if(param1.txt_menu != null)
            {
               param1.txt_menu.SetText(String(ExternalInterface.call("MessageConvert",param2)));
            }
         }
      }
   }
}

