package script.net_set
{
   import Enum.Enum_NetLabel;
   import Enum.Enum_NetLabelSession;
   import InputPad.InputPadKeyCode;
   import KeyHelp.KeyHelpCode;
   import Select.UiSelect;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.ExternalInterface;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public class nut_menu extends MovieClip
   {
      
      public var mc_set:anm_set;
      
      public var mc_setbar01:anm_setbar;
      
      public var mc_win:anm_win;
      
      public var mc_setbar00:anm_setbar;
      
      public var CallSetStepEnd:Function;
      
      public var CallSetStepCancel:Function;
      
      public var CallCallRoomName:Function;
      
      private var m_keyHelp:KeyHelpCode;
      
      private var m_lock:Boolean = false;
      
      private var m_isAgingMode:Boolean = false;
      
      internal var text_window_title:Array = ["networkmode_442","networkmode_428"];
      
      internal var text_bar_title:Array = ["networkmode_440","networkmode_440","networkmode_166","networkmode_122","networkmode_430","networkmode_552","networkmode_552","network_sys_011","network_sys_020","networkmode_551","networkmode_040","networkmode_432","networkmode_150","networkmode_","networkmode_122","network_sys_011","network_sys_214","network_sys_214","network_sys_020","networkmode_645","networkmode_645","ppt_name","ppt_name"];
      
      internal var text_bar_text_e_num:Array = ["networkmode_567","networkmode_568","networkmode_569","networkmode_570","networkmode_571","networkmode_572","networkmode_573"];
      
      internal var text_bar_text_t_num:Array = ["networkmode_569","networkmode_573"];
      
      internal var text_bar_text_room:Array = ["networkmode_168","networkmode_","networkmode_"];
      
      internal var text_bar_text_compare3:Array = ["networkmode_168","networkmode_167","networkmode_265"];
      
      internal var text_bar_text_compare4:Array = ["networkmode_168","network_sys_013","network_sys_012"];
      
      internal var text_bar_text_compare2:Array = ["networkmode_168","networkmode_167"];
      
      internal var text_bar_text_onoff:Array = ["networkmode_057","networkmode_056"];
      
      internal var text_bar_text_noyes:Array = ["network_sys_013","network_sys_012"];
      
      internal var text_bar_text_onoff_search:Array = ["networkmode_168","networkmode_057","networkmode_056"];
      
      internal var text_bar_text_noyes_search:Array = ["networkmode_168","network_sys_013","network_sys_012"];
      
      internal var text_bar_text_team_create:Array = ["freebattle_007","freebattle_008"];
      
      internal var text_bar_text_team_search:Array = ["networkmode_168","freebattle_007","freebattle_008"];
      
      internal var text_bar_text_strength:Array = ["networkmode_168","networkmode_","networkmode_","networkmode_"];
      
      internal var text_bar_text_battleprogless_create:Array = ["network_sys_215","network_sys_216"];
      
      internal var text_bar_text_battleprogless_search:Array = ["networkmode_168","network_sys_215","network_sys_216"];
      
      internal var text_bar_text_round_create:Array = ["networkmode_646","networkmode_568","networkmode_570","networkmode_572","practice_Exercises_008"];
      
      internal var text_bar_text_round_search:Array = ["networkmode_168","networkmode_646","networkmode_568","networkmode_570","networkmode_572","practice_Exercises_008"];
      
      internal var m_init:Boolean = false;
      
      internal var m_end:Boolean = false;
      
      internal var m_anmend:Boolean = false;
      
      internal var m_cancel:Boolean = false;
      
      internal var m_type:Number = 100;
      
      internal var m_setcriate:Boolean = true;
      
      private var m_inputPad:InputPadKeyCode;
      
      private var m_select1:UiSelect;
      
      private var m_select2:UiSelect;
      
      internal var selItem1:Number = 0;
      
      internal var selItem2:Number = 0;
      
      internal var selItem1ValueMax:Number = 0;
      
      internal var selItem2ValueMax:Number = 0;
      
      internal var selItemSave1:Number = -1;
      
      internal var selItemSave2:Number = -1;
      
      internal var side:int = 0;
      
      internal var m_listType:Array = new Array();
      
      internal var m_listMc:Array = new Array();
      
      internal var m_anser_Set:Array = new Array();
      
      internal var m_anser:Array = new Array();
      
      internal var _pos_bar_start_x:Number = 0;
      
      internal var _pos_bar_start_y:Number = 0;
      
      internal var _pos_bar_space_x:Number = 0;
      
      internal var _pos_bar_space_y:Number = 0;
      
      internal var _pos_bar_size_x:Number = 0;
      
      internal var _pos_bar_size_y:Number = 0;
      
      internal var _pos_barb_x:Number = 0;
      
      internal var _pos_barb_y:Number = 0;
      
      internal var roomname:String = "";
      
      internal var keypush:Boolean = false;
      
      internal var m_RoomNameLock:Boolean = false;
      
      public function nut_menu()
      {
         super();
         addFrameScript(5,this.frame6,10,this.frame11);
         this.m_keyHelp = new KeyHelpCode();
         this._pos_bar_start_x = this.mc_setbar00.x - this.mc_win.x;
         this._pos_bar_start_y = this.mc_setbar00.y - this.mc_win.y;
         this._pos_bar_space_x = this.mc_setbar01.x - this.mc_setbar00.x;
         this._pos_bar_space_y = this.mc_setbar01.y - this.mc_setbar00.y;
         this._pos_bar_size_x = this.mc_setbar00.width;
         this._pos_bar_size_y = this.mc_setbar00.height;
         this._pos_barb_x = this.mc_set.x - this.mc_setbar01.x;
         this._pos_barb_y = this.mc_set.y - this.mc_setbar01.y;
         removeChild(this.mc_setbar00);
         removeChild(this.mc_setbar01);
         removeChild(this.mc_set);
         this.m_inputPad = new InputPadKeyCode();
         this.m_select1 = new UiSelect();
         this.m_select1.InitSelect(0,0,2,this.m_inputPad.GetKeyInputBtn_L_Up(),this.m_inputPad.GetKeyInputBtn_L_Down(),UiSelect.CCD_LOOP_TYPE_DISABLE);
         this.m_select1.SetEnablePad(this.side);
         this.m_select1.SetDisablePad(1 - this.side);
         this.m_select1.SetLoopType(UiSelect.CCD_LOOP_TYPE_PUSH);
         this.m_select2 = new UiSelect();
         this.m_select2.InitSelect(0,0,10,this.m_inputPad.GetKeyInputBtn_L_Left(),this.m_inputPad.GetKeyInputBtn_L_Right(),UiSelect.CCD_LOOP_TYPE_DISABLE);
         this.m_select2.SetEnablePad(this.side);
         this.m_select2.SetDisablePad(1 - this.side);
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
      }
      
      public function setType(param1:Number) : *
      {
         this.m_type = param1;
         switch(this.m_type)
         {
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_CREATE_RANK:
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_CREATE_PLAYER:
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_CREATE_ENDLESS:
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_CREATE_LEAGUE:
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_CREATE_TOURNAMENT:
               this.m_setcriate = true;
               break;
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_SEARCH_RANK:
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_SEARCH_PLAYER:
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_SEARCH_ENDLESS:
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_SEARCH_LEAGUE:
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_SEARCH_TOURNAMENT:
               this.m_setcriate = false;
         }
      }
      
      public function Initialize(param1:Function, param2:Function, param3:Function) : *
      {
         var _loc5_:Number = NaN;
         var _loc4_:Number = 0;
         if(param1 != null)
         {
            this.CallSetStepEnd = param1;
            this.CallSetStepCancel = param2;
            this.CallCallRoomName = param3;
         }
         this.setWindowTitle();
         this.m_listType = this.getSettingList(this.m_type);
         _loc5_ = this.m_listType.length - 2;
         if(_loc5_ <= -1)
         {
            _loc5_++;
         }
         var _loc6_:Number = _loc5_ * this._pos_bar_space_y;
         this.mc_win.mc_win.height += _loc6_;
         this.mc_win.all_deco1.y += _loc5_ * this._pos_bar_space_y;
         _loc6_ /= 2;
         this.mc_win.mc_win.y += _loc6_;
         this.y -= _loc6_;
         var _loc7_:* = this._pos_bar_start_x;
         var _loc8_:* = this._pos_bar_start_y;
         _loc4_ = 0;
         while(_loc4_ < this.m_listType.length)
         {
            this.m_listMc.push(this.CreateBar(this.m_listType[_loc4_],_loc7_,_loc8_,_loc4_));
            _loc7_ += this._pos_bar_space_x;
            _loc8_ += this._pos_bar_space_y;
            _loc4_++;
         }
         this.m_listMc.push(this.CreateBarEnter(_loc7_ + this._pos_barb_x - this._pos_bar_space_x,_loc8_ + this._pos_barb_y - this._pos_bar_space_y));
         this.setSelectValue1();
         this.setSelectValue2();
         this.m_init = true;
         this.m_end = false;
         this.m_anmend = false;
         this.m_cancel = false;
         this.MenuKeyHelp(this.selItemSave1);
         this.gotoAndPlay("in");
         ExternalInterface.call("PushScrollHelp");
         if(this.m_type == Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_CREATE_ENDLESS)
         {
            this.m_select1.SetSelValue(9);
         }
      }
      
      public function setSelectValue1() : void
      {
         this.selItem1ValueMax = this.m_listType.length;
         this.m_select1.SetMinValue(0);
         this.m_select1.SetMaxValue(this.selItem1ValueMax);
         this.m_select1.SetSelValue(0);
      }
      
      public function setSelectValue2() : void
      {
         if(this.selItem1 == this.m_listType.length)
         {
            return;
         }
         this.selItem1 = this.m_select1.GetSelValue();
         var _loc1_:Array = this.getBarTextList(this.m_listType[this.selItem1]);
         if(_loc1_ != null)
         {
            this.selItem2ValueMax = _loc1_.length - 1;
            this.selItem2 = this.m_anser[this.selItem1];
            this.selItemSave2 = this.selItem2;
            this.MenuScrollHelp(this.m_listType[this.selItemSave1],this.selItemSave2);
            this.m_select2.SetMinValue(0);
            this.m_select2.SetMaxValue(this.selItem2ValueMax);
            this.m_select2.SetSelValue(this.selItem2);
         }
      }
      
      public function MenuKeyHelp(param1:Number) : void
      {
         if(this.keypush == true)
         {
            this.m_keyHelp.PopKeyHelp();
            this.keypush = false;
         }
         if(this.m_listType[param1] == Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME || param1 == this.m_listType.length)
         {
            this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
         }
         this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
         this.m_keyHelp.PushKeyHelp();
         this.keypush = true;
      }
      
      public function MenuScrollHelp(param1:Number, param2:Number) : void
      {
         if(this.m_listType.length == this.selItemSave1)
         {
            if(this.m_setcriate)
            {
               ExternalInterface.call("SetScrollHelpId","endless_010");
            }
            else
            {
               ExternalInterface.call("SetScrollHelpId","endless_011");
            }
            return;
         }
         switch(param1)
         {
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_E_MEMBER_NUM:
               ExternalInterface.call("SetScrollHelpId","networkmode_449");
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_T_MEMBER_NUM:
               ExternalInterface.call("SetScrollHelpId","networkmode_449");
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_RANK:
               switch(param2)
               {
                  case 0:
                     ExternalInterface.call("SetScrollHelpId","networkmode_433");
                     break;
                  case 1:
                     ExternalInterface.call("SetScrollHelpId","networkmode_435");
                     break;
                  case 2:
                     ExternalInterface.call("SetScrollHelpId","networkmode_434");
               }
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TEAM_CREATE:
               switch(param2)
               {
                  case 0:
                     ExternalInterface.call("SetScrollHelpId","networkmode_131");
                     break;
                  case 1:
                     ExternalInterface.call("SetScrollHelpId","networkmode_132");
               }
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_REGION:
               switch(param2)
               {
                  case 0:
                     ExternalInterface.call("SetScrollHelpId","networkmode_447");
                     break;
                  case 1:
                     ExternalInterface.call("SetScrollHelpId","networkmode_438");
               }
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PRIVATE:
               switch(param2)
               {
                  case 0:
                     ExternalInterface.call("SetScrollHelpId","networkmode_667");
                     break;
                  case 1:
                     ExternalInterface.call("SetScrollHelpId","networkmode_668");
               }
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PRIVATE_PLURAL:
               ExternalInterface.call("SetScrollHelpId","_");
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_EXIT_LOSER_CREATE:
               ExternalInterface.call("SetScrollHelpId","network_sys_144");
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PHANTAMAGORIA_CREATE:
               ExternalInterface.call("SetScrollHelpId","network_sys_143");
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME:
               ExternalInterface.call("SetScrollHelpId","networkmode_550");
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_CREATE:
               ExternalInterface.call("SetScrollHelpId","endless_010");
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_SEARCH:
               ExternalInterface.call("SetScrollHelpId","endless_011");
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_FRIEND:
               ExternalInterface.call("SetScrollHelpId","_");
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_STRENGTH:
               ExternalInterface.call("SetScrollHelpId","_");
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TEAM_SEARCH:
               switch(param2)
               {
                  case 0:
                     ExternalInterface.call("SetScrollHelpId","networkmode_130");
                     break;
                  case 1:
                     ExternalInterface.call("SetScrollHelpId","networkmode_131");
                     break;
                  case 2:
                     ExternalInterface.call("SetScrollHelpId","networkmode_132");
               }
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_EXIT_LOSER_SEARCH:
               ExternalInterface.call("SetScrollHelpId","network_sys_144");
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_BATTLEPROGLESS_CREATE:
               switch(param2)
               {
                  case 0:
                     ExternalInterface.call("SetScrollHelpId","networkmode_548");
                     break;
                  case 1:
                     ExternalInterface.call("SetScrollHelpId","networkmode_549");
               }
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_BATTLEPROGLESS_SEARCH:
               switch(param2)
               {
                  case 0:
                     ExternalInterface.call("SetScrollHelpId","networkmode_547");
                     break;
                  case 1:
                     ExternalInterface.call("SetScrollHelpId","networkmode_548");
                     break;
                  case 2:
                     ExternalInterface.call("SetScrollHelpId","networkmode_549");
               }
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PHANTAMAGORIA_SEARCH:
               ExternalInterface.call("SetScrollHelpId","network_sys_143");
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROUNDSET_CREATE:
               switch(param2)
               {
                  case 0:
                     ExternalInterface.call("SetScrollHelpId","networkmode_649");
                     break;
                  case 1:
                     ExternalInterface.call("SetScrollHelpId","networkmode_648");
                     break;
                  case 2:
                     ExternalInterface.call("SetScrollHelpId","evo_round5");
                     break;
                  case 3:
                     ExternalInterface.call("SetScrollHelpId","evo_round7");
                     break;
                  case 4:
                     ExternalInterface.call("SetScrollHelpId","evo_round9");
               }
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROUNDSET_SEARCH:
               switch(param2)
               {
                  case 0:
                     ExternalInterface.call("SetScrollHelpId","networkmode_647");
                     break;
                  case 1:
                     ExternalInterface.call("SetScrollHelpId","networkmode_649");
                     break;
                  case 2:
                     ExternalInterface.call("SetScrollHelpId","networkmode_648");
                     break;
                  case 3:
                     ExternalInterface.call("SetScrollHelpId","evo_round5");
                     break;
                  case 4:
                     ExternalInterface.call("SetScrollHelpId","evo_round7");
                     break;
                  case 5:
                     ExternalInterface.call("SetScrollHelpId","evo_round9");
               }
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TOPOGRAPHY_CREATE:
               switch(param2)
               {
                  case 0:
                     ExternalInterface.call("SetScrollHelpId","ppt_online");
                     break;
                  case 1:
                     ExternalInterface.call("SetScrollHelpId","ppt_online");
               }
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TOPOGRAPHY_SEARCH:
               switch(param2)
               {
                  case 0:
                     ExternalInterface.call("SetScrollHelpId","ppt_online");
                     break;
                  case 1:
                     ExternalInterface.call("SetScrollHelpId","ppt_online");
                     break;
                  case 2:
                     ExternalInterface.call("SetScrollHelpId","ppt_online");
               }
         }
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         if(this.m_anmend == true || this.m_RoomNameLock == true || this.m_lock == true)
         {
            return;
         }
         this.update();
         if(this.currentFrame == this.totalFrames)
         {
            ExternalInterface.call("PopScrollHelp");
            this.m_anmend = true;
            if(this.keypush == true)
            {
               this.m_keyHelp.PopKeyHelp();
               this.keypush = false;
            }
            if(this.CallSetStepCancel != null && this.m_cancel == true)
            {
               this.CallSetStepCancel();
               this.CallSetStepEnd();
            }
            else if(this.CallSetStepEnd != null)
            {
               this.CallSetStepEnd();
            }
            else
            {
               trace("[error] nut_setting onEnterFrameCtrl CallSetStepEnd");
            }
         }
      }
      
      public function update() : void
      {
         var _loc1_:Number = 0;
         if(this.m_init == false || this.m_end == true || this.m_cancel == true)
         {
            return;
         }
         if(this.m_isAgingMode == true)
         {
            this.gotoAndPlay("out");
            this.m_end = true;
            return;
         }
         this.m_select1.SelectMenuCtrl();
         this.selItem1 = this.m_select1.GetSelValue();
         if(this.selItemSave1 != this.selItem1)
         {
            this.setSelectValue2();
            if(this.selItem1 == this.m_listType.length)
            {
               this.m_listMc[this.m_listType.length].gotoAndStop("on");
            }
            else
            {
               this.m_listMc[this.m_listType.length].gotoAndStop("off");
            }
            _loc1_ = 0;
            while(_loc1_ < this.m_listType.length)
            {
               if(this.m_listMc[_loc1_] != null)
               {
                  this.selItem2 = this.m_anser[this.selItem1];
                  if(_loc1_ == this.selItem1)
                  {
                     if(this.m_listType[_loc1_] == Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME)
                     {
                        if(this.roomname == null || this.roomname == "")
                        {
                           this.m_listMc[_loc1_].gotoAndStop("room_on");
                           this.m_listMc[_loc1_].txt_slct.SetText(String(ExternalInterface.call("MessageConvert","networkmode_553")));
                        }
                        else
                        {
                           this.m_listMc[_loc1_].gotoAndStop("room_on");
                           this.m_listMc[_loc1_].txt_slct.SetText(String(ExternalInterface.call("MessageConvert",this.roomname)));
                        }
                     }
                     else
                     {
                        this.m_listMc[_loc1_].gotoAndStop("set_on");
                        if(this.selItem2 == 0)
                        {
                           this.m_listMc[_loc1_].all_cursor_m_l.visible = false;
                        }
                        else
                        {
                           this.m_listMc[_loc1_].all_cursor_m_l.visible = true;
                        }
                        if(this.selItem2 == this.selItem2ValueMax)
                        {
                           this.m_listMc[_loc1_].all_cursor_m_r.visible = false;
                        }
                        else
                        {
                           this.m_listMc[_loc1_].all_cursor_m_r.visible = true;
                        }
                     }
                  }
                  else if(this.m_listType[_loc1_] == Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME)
                  {
                     if(this.roomname == null || this.roomname == "")
                     {
                        this.m_listMc[_loc1_].gotoAndStop("room_off");
                        this.m_listMc[_loc1_].txt_slct.SetText(String(ExternalInterface.call("MessageConvert","networkmode_553")));
                     }
                     else
                     {
                        this.m_listMc[_loc1_].gotoAndStop("room_off");
                        this.m_listMc[_loc1_].txt_slct.SetText(String(ExternalInterface.call("MessageConvert",this.roomname)));
                     }
                  }
                  else
                  {
                     this.m_listMc[_loc1_].gotoAndStop("set_off");
                     this.m_listMc[_loc1_].all_cursor_m_l.visible = false;
                     this.m_listMc[_loc1_].all_cursor_m_r.visible = false;
                  }
               }
               _loc1_++;
            }
            this.selItemSave1 = this.selItem1;
            this.MenuKeyHelp(this.selItemSave1);
            ExternalInterface.call("RequestPlaySE_Select");
            this.MenuScrollHelp(this.m_listType[this.selItemSave1],this.selItemSave2);
         }
         if(this.selItem1 < this.m_listType.length)
         {
            this.m_select2.SelectMenuCtrl();
            this.selItem2 = this.m_select2.GetSelValue();
            if(this.selItemSave2 != this.selItem2)
            {
               this.m_anser[this.selItem1] = this.selItem2;
               this.setBarText(this.m_listMc[this.selItem1],this.m_listType[this.selItem1],this.m_anser[this.selItem1]);
               if(this.m_listType[this.selItem1] != Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME)
               {
                  if(this.selItem2 == 0)
                  {
                     this.m_listMc[this.selItem1].all_cursor_m_l.visible = false;
                  }
                  else
                  {
                     this.m_listMc[this.selItem1].all_cursor_m_l.visible = true;
                  }
                  if(this.selItem2 == this.selItem2ValueMax)
                  {
                     this.m_listMc[this.selItem1].all_cursor_m_r.visible = false;
                  }
                  else
                  {
                     this.m_listMc[this.selItem1].all_cursor_m_r.visible = true;
                  }
                  ExternalInterface.call("RequestPlaySE_Select");
               }
               this.selItemSave2 = this.selItem2;
               this.MenuScrollHelp(this.m_listType[this.selItemSave1],this.selItemSave2);
            }
         }
         if(this.m_inputPad.GetKeyInputBtn_Cancel() == this.m_inputPad.GetPadPress())
         {
            ExternalInterface.call("RequestPlaySE_Cancel");
            this.gotoAndPlay("out");
            this.m_cancel = true;
            this.m_end = true;
         }
         else if(this.selItem1 == this.m_listType.length)
         {
            if(this.m_inputPad.GetKeyInputBtn_Ok() == this.m_inputPad.GetPadPress())
            {
               ExternalInterface.call("RequestPlaySE_Fix");
               this.gotoAndPlay("out");
               this.m_end = true;
            }
         }
         else if(this.m_listType[this.selItem1] == Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME)
         {
            if(this.m_inputPad.GetKeyInputBtn_Ok() == this.m_inputPad.GetPadPress())
            {
               this.m_RoomNameLock = true;
               this.CallCallRoomName();
               ExternalInterface.call("RequestPlaySE_Fix");
            }
         }
      }
      
      public function CreateBar(param1:Number, param2:Number, param3:Number, param4:Number) : MovieClip
      {
         var _loc5_:anm_setbar = null;
         _loc5_ = new anm_setbar();
         _loc5_.name = "bar_no" + param4;
         _loc5_.x = param2;
         _loc5_.y = param3;
         this.mc_win.addChild(_loc5_);
         _loc5_.width = this._pos_bar_size_x;
         _loc5_.height = this._pos_bar_size_y;
         this.m_anser.push(0);
         this.setBarTitle(_loc5_,param1);
         this.setBarText(_loc5_,param1,0);
         return _loc5_;
      }
      
      public function CreateBarEnter(param1:Number, param2:Number) : MovieClip
      {
         var _loc3_:anm_set = new anm_set();
         _loc3_.x = param1;
         _loc3_.y = param2;
         if(this.m_setcriate == true)
         {
            _loc3_.txt_set.SetText(String(ExternalInterface.call("MessageConvert","networkmode_040")));
         }
         else
         {
            _loc3_.txt_set.SetText(String(ExternalInterface.call("MessageConvert","networkmode_432")));
         }
         this.mc_win.addChild(_loc3_);
         return _loc3_;
      }
      
      public function setWindowTitle() : *
      {
         if(this.mc_win.txt_head == null)
         {
            trace(" setWindowTitle mc_head null");
         }
         if(this.mc_win.txt_head == null)
         {
            trace(" setWindowTitle mc_head.txt_head null");
         }
         if(this.m_setcriate == true)
         {
            this.mc_win.txt_head.SetText(String(ExternalInterface.call("MessageConvert",this.text_window_title[0])));
         }
         else
         {
            this.mc_win.txt_head.SetText(String(ExternalInterface.call("MessageConvert",this.text_window_title[1])));
         }
      }
      
      public function setBarTitle(param1:MovieClip, param2:Number) : *
      {
         param1.txt_title.SetText(String(ExternalInterface.call("MessageConvert",this.text_bar_title[param2])));
      }
      
      public function setBarText(param1:MovieClip, param2:Number, param3:Number) : *
      {
         var _loc4_:Array = null;
         var _loc5_:smb_font = null;
         var _loc6_:MovieClip = null;
         var _loc7_:MovieClip = null;
         _loc4_ = this.getBarTextList(param2);
         if(_loc4_ != null && param1 != null)
         {
            if(param3 < _loc4_.length)
            {
               this.selItem1 = this.m_select1.GetSelValue();
               _loc5_ = smb_font(param1.getChildByName("txt_slct"));
               if(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME != param2)
               {
                  if(_loc5_)
                  {
                     _loc5_.SetText(String(ExternalInterface.call("MessageConvert",_loc4_[param3])));
                  }
                  _loc6_ = MovieClip(param1.getChildByName("all_cursor_m_l"));
                  _loc7_ = MovieClip(param1.getChildByName("all_cursor_m_r"));
                  if(_loc6_)
                  {
                     if(param3 == 0)
                     {
                        _loc6_.visible = false;
                     }
                     else
                     {
                        _loc6_.visible = true;
                     }
                  }
                  if(_loc7_)
                  {
                     if(param3 == _loc4_.length)
                     {
                        _loc7_.visible = false;
                     }
                     else
                     {
                        _loc7_.visible = true;
                     }
                  }
               }
            }
            else
            {
               trace("[error] nut_setting setBarText text_list.length over type : " + param2 + " _ " + "no : " + param3);
            }
         }
         else
         {
            trace("[error] nut_setting setBarText mc : " + param1);
         }
      }
      
      public function getBarTextList(param1:Number) : Array
      {
         var _loc2_:Array = null;
         switch(param1)
         {
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_E_MEMBER_NUM:
               _loc2_ = this.text_bar_text_e_num;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_T_MEMBER_NUM:
               _loc2_ = this.text_bar_text_t_num;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_RANK:
               _loc2_ = this.text_bar_text_compare3;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TEAM_CREATE:
               _loc2_ = this.text_bar_text_team_create;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_REGION:
               _loc2_ = this.text_bar_text_compare2;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PRIVATE:
               _loc2_ = this.text_bar_text_onoff;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PRIVATE_PLURAL:
               _loc2_ = this.text_bar_text_onoff;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_EXIT_LOSER_CREATE:
               _loc2_ = this.text_bar_text_onoff;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PHANTAMAGORIA_CREATE:
               _loc2_ = this.text_bar_text_onoff;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME:
               _loc2_ = this.text_bar_text_room;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_CREATE:
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_SEARCH:
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_FRIEND:
               _loc2_ = this.text_bar_text_onoff;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_STRENGTH:
               _loc2_ = this.text_bar_text_strength;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TEAM_SEARCH:
               _loc2_ = this.text_bar_text_team_search;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_EXIT_LOSER_SEARCH:
               _loc2_ = this.text_bar_text_onoff_search;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_BATTLEPROGLESS_CREATE:
               _loc2_ = this.text_bar_text_battleprogless_create;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_BATTLEPROGLESS_SEARCH:
               _loc2_ = this.text_bar_text_battleprogless_search;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PHANTAMAGORIA_SEARCH:
               _loc2_ = this.text_bar_text_onoff_search;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROUNDSET_CREATE:
               _loc2_ = this.text_bar_text_round_create;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROUNDSET_SEARCH:
               _loc2_ = this.text_bar_text_round_search;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TOPOGRAPHY_CREATE:
               _loc2_ = this.text_bar_text_onoff;
               break;
            case Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TOPOGRAPHY_SEARCH:
               _loc2_ = this.text_bar_text_onoff_search;
         }
         return _loc2_;
      }
      
      public function getSettingList(param1:Number) : Array
      {
         var _loc2_:Array = new Array();
         switch(param1)
         {
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_CREATE_RANK:
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_REGION);
               break;
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_CREATE_PLAYER:
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TEAM_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROUNDSET_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_REGION);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PRIVATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PHANTAMAGORIA_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TOPOGRAPHY_CREATE);
               break;
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_CREATE_ENDLESS:
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_E_MEMBER_NUM);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PRIVATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TEAM_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROUNDSET_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_REGION);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_EXIT_LOSER_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PHANTAMAGORIA_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TOPOGRAPHY_CREATE);
               break;
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_CREATE_LEAGUE:
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PRIVATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TEAM_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROUNDSET_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_BATTLEPROGLESS_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_REGION);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PHANTAMAGORIA_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TOPOGRAPHY_CREATE);
               break;
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_CREATE_TOURNAMENT:
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_T_MEMBER_NUM);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PRIVATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TEAM_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROUNDSET_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_BATTLEPROGLESS_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_REGION);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PHANTAMAGORIA_CREATE);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TOPOGRAPHY_CREATE);
               break;
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_SEARCH_RANK:
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_RANK);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_REGION);
               break;
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_SEARCH_PLAYER:
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TEAM_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROUNDSET_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_REGION);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PHANTAMAGORIA_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TOPOGRAPHY_SEARCH);
               break;
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_SEARCH_ENDLESS:
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TEAM_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROUNDSET_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_REGION);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_EXIT_LOSER_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PHANTAMAGORIA_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TOPOGRAPHY_SEARCH);
               break;
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_SEARCH_LEAGUE:
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TEAM_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROUNDSET_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_REGION);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PHANTAMAGORIA_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_BATTLEPROGLESS_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TOPOGRAPHY_SEARCH);
               break;
            case Enum_NetLabel.CCD_UI_NET_SESSIONSET_TYPE_SEARCH_TOURNAMENT:
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TEAM_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROUNDSET_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_REGION);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_PHANTAMAGORIA_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_BATTLEPROGLESS_SEARCH);
               _loc2_.push(Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_TOPOGRAPHY_SEARCH);
         }
         return _loc2_;
      }
      
      public function setLock() : void
      {
         this.m_lock = true;
      }
      
      public function setUnLock() : void
      {
         this.m_lock = false;
      }
      
      public function setRoomName(param1:String) : void
      {
         this.roomname = param1;
         var _loc2_:Number = 0;
         _loc2_ = 0;
         while(_loc2_ < this.m_listType.length)
         {
            if(this.m_listMc[_loc2_] != null)
            {
               if(_loc2_ == this.selItem1)
               {
                  if(this.m_listType[_loc2_] == Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME)
                  {
                     if(this.roomname == null || this.roomname == "")
                     {
                        this.m_listMc[_loc2_].gotoAndStop("room_on");
                        this.m_listMc[_loc2_].txt_slct.SetText(String(ExternalInterface.call("MessageConvert","networkmode_553")));
                     }
                     else
                     {
                        this.m_listMc[_loc2_].gotoAndStop("room_on");
                        this.m_listMc[_loc2_].txt_slct.SetText(String(ExternalInterface.call("MessageConvert",this.roomname)));
                     }
                  }
               }
               else if(this.m_listType[_loc2_] == Enum_NetLabelSession.CCD_UI_NET_SESSIONSET_ROOM_NAME)
               {
                  if(this.roomname == null || this.roomname == "")
                  {
                     this.m_listMc[_loc2_].gotoAndStop("room_off");
                     this.m_listMc[_loc2_].txt_slct.SetText(String(ExternalInterface.call("MessageConvert","networkmode_553")));
                  }
                  else
                  {
                     this.m_listMc[_loc2_].gotoAndStop("room_off");
                     this.m_listMc[_loc2_].txt_slct.SetText(String(ExternalInterface.call("MessageConvert",this.roomname)));
                  }
               }
            }
            _loc2_++;
         }
      }
      
      public function setSetting(param1:Number, param2:Number) : void
      {
         var _loc3_:Number = 0;
         while(_loc3_ < this.m_listType.length)
         {
            if(this.m_listType[_loc3_] == param1)
            {
               this.m_anser[_loc3_] = param2;
               this.setBarText(this.m_listMc[_loc3_],param1,param2);
               break;
            }
            _loc3_++;
         }
      }
      
      public function getSettingNum() : int
      {
         return int(int(this.m_listType.length));
      }
      
      public function setRoomNameEnd() : void
      {
         this.m_RoomNameLock = false;
      }
      
      public function getSettingAnserType(param1:Number) : int
      {
         if(param1 >= this.m_listType.length)
         {
            trace("[error] nut_setting getSettingAnserType no = " + param1);
            return 0;
         }
         return int(this.m_listType[param1]);
      }
      
      public function getSettingAnserValue(param1:Number) : int
      {
         if(param1 >= this.m_anser.length)
         {
            trace("[error] nut_setting getSettingAnserValue no = " + param1);
            return 0;
         }
         return int(this.m_anser[param1]);
      }
      
      public function EnableAgingMode() : *
      {
         this.m_isAgingMode = true;
      }
      
      internal function frame6() : *
      {
         stop();
      }
      
      internal function frame11() : *
      {
         stop();
      }
   }
}

