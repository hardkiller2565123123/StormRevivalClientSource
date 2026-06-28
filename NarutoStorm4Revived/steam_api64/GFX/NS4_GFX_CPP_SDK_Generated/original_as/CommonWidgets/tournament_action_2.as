package script.freebtl_tonmt
{
   import InputPad.InputPadKeyCode;
   import KeyHelp.KeyHelpCode;
   import SeIdList.SeId;
   import Select.UiSelect;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import script.xcmn_font.smb_font;
   
   public class tournament_action
   {
      
      internal static const CCD_TYPE_TOURNAMENT_ALLNUM_P4:Number = 4;
      
      internal static const CCD_TYPE_TOURNAMENT_ALLNUM_P8:Number = 8;
      
      internal static const CCD_TYPE_TOURNAMENT_ALLNUM_ALL:Number = 8;
      
      internal static const CCD_TYPE_TOURNAMENT_RESULTENUM_P4:Number = 3;
      
      internal static const CCD_TYPE_TOURNAMENT_RESULTENUM_P8:Number = 7;
      
      public var CallStepAnmEnd:Function = null;
      
      public var CallStepFinish:Function = null;
      
      public var CallStepSetEnd:Function = null;
      
      public var CallSetMode:Function = null;
      
      public var CallRequest2pController:Function = null;
      
      public var CallShufflePlayer:Function = null;
      
      public var CallSwapPlayer:Function = null;
      
      public var CallFixPlayer:Function = null;
      
      public var CallCancel:Function = null;
      
      private var resultmode:int = 2000;
      
      private var resultmode_log:int = this.resultmode;
      
      private var m_mc:MovieClip = null;
      
      private var m_user:Array = new Array(8);
      
      private var m_user_num:int = 0;
      
      private var DeadUser:int = -1;
      
      private var m_select1:UiSelect = null;
      
      private var m_inputPad:InputPadKeyCode = null;
      
      private var m_keyHelp:* = null;
      
      private var flag_steplast:Boolean = false;
      
      private var flag_last:Boolean = false;
      
      private var resultcount:int = 0;
      
      private var resultcountStop:int = 99;
      
      private var resultmodeAnm_mc:MovieClip = null;
      
      private var m_guest:Boolean = false;
      
      private var m_first:Boolean = false;
      
      private var m_net:Boolean = false;
      
      private var isSpecial:Boolean = false;
      
      private var isStart:Boolean = false;
      
      private var enableSetting:Boolean = true;
      
      private var isAllChange:Boolean = false;
      
      private var enable2pController:Boolean = false;
      
      public var isPS4:Boolean = false;
      
      internal var keypush:Boolean = false;
      
      internal var m_isPushScroll:Boolean = false;
      
      private var m_skip:Boolean = false;
      
      internal var dinit:Boolean = false;
      
      internal var AnimAns:* = -1;
      
      internal var mode_Change_1:int = -1;
      
      internal var mode_Change_2:int = -1;
      
      internal var Change_mode:* = -1;
      
      internal var Change_no1:* = -1;
      
      internal var Change_no2:* = -1;
      
      internal var m_select_no:int = 0;
      
      public function tournament_action()
      {
         super();
         var _loc1_:int = 0;
         if(this.m_inputPad == null)
         {
            this.m_inputPad = new InputPadKeyCode();
         }
         if(this.m_inputPad != null)
         {
            this.m_select1 = new UiSelect();
            this.m_select1.InitSelect(1,1,3,this.m_inputPad.GetKeyInputBtn_L_Up(),this.m_inputPad.GetKeyInputBtn_L_Down(),UiSelect.CCD_LOOP_TYPE_DISABLE);
         }
         if(this.m_keyHelp == null)
         {
            this.m_keyHelp = new KeyHelpCode();
         }
         _loc1_ = 0;
         while(_loc1_ < CCD_TYPE_TOURNAMENT_ALLNUM_ALL)
         {
            this.m_user[_loc1_] = new tournament_member();
            _loc1_++;
         }
         this.clear();
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_BOOK);
      }
      
      public function clear() : void
      {
         var _loc1_:int = 0;
         this.resultmode = 2000;
         this.resultcount = 0;
         _loc1_ = 0;
         while(_loc1_ < CCD_TYPE_TOURNAMENT_ALLNUM_ALL)
         {
            this.m_user[_loc1_].clear();
            _loc1_++;
         }
      }
      
      public function setFunction(param1:Function, param2:Function, param3:Function, param4:Function, param5:Function, param6:Function, param7:Function, param8:*) : void
      {
         this.CallStepAnmEnd = param1;
         this.CallStepFinish = param2;
         this.CallStepSetEnd = param3;
         this.CallSetMode = param4;
         this.CallRequest2pController = param5;
         this.CallShufflePlayer = param6;
         this.CallSwapPlayer = param7;
         this.CallFixPlayer = param8;
      }
      
      public function init() : void
      {
         var _loc5_:MovieClip = null;
         this.clear();
         this.m_mc.all_credit.visible = false;
         var _loc1_:smb_font = this.m_mc.all_credit.mc_credit.getChildByName("txt_credit00") as smb_font;
         if(_loc1_ != null)
         {
            if(this.isPS4)
            {
               _loc1_.SetText(String(ExternalInterface.call("MessageConvert","option_103")));
            }
            else
            {
               _loc1_.SetText(String(ExternalInterface.call("MessageConvert","option_153")));
            }
            _loc1_.SetTextPivot(smb_font.CCD_PIVOT_CC);
            _loc5_ = this.m_mc.all_credit.mc_credit.getChildByName("mc_credit00") as MovieClip;
            _loc5_.width = _loc1_.GetTextFieldWidth() + 60;
            _loc5_.height = _loc1_.GetTextFieldHeight() + 60;
            _loc5_.alpha = 1;
         }
         var _loc2_:MovieClip = this.m_mc.all_title.getChildByName("mc_title") as MovieClip;
         if(_loc2_ != null)
         {
            if(this.isSpecial)
            {
               _loc2_.gotoAndStop("rand");
            }
            else
            {
               _loc2_.gotoAndStop("free");
            }
         }
         var _loc3_:tournament_member = new tournament_member();
         var _loc4_:int = 0;
         this.init_borad();
         if(this.m_user_num == CCD_TYPE_TOURNAMENT_ALLNUM_P4)
         {
            _loc4_ = 0;
            while(_loc4_ < 4)
            {
               _loc3_.clear();
               if(_loc4_ == 0)
               {
                  _loc3_.part = this.m_mc.all_charlist_4.mc_namebar_00;
               }
               if(_loc4_ == 1)
               {
                  _loc3_.part = this.m_mc.all_charlist_4.mc_namebar_01;
               }
               if(_loc4_ == 2)
               {
                  _loc3_.part = this.m_mc.all_charlist_4.mc_namebar_02;
               }
               if(_loc4_ == 3)
               {
                  _loc3_.part = this.m_mc.all_charlist_4.mc_namebar_03;
               }
               this.setUser(_loc4_,_loc3_);
               _loc4_++;
            }
         }
         else
         {
            _loc4_ = 0;
            while(_loc4_ < 8)
            {
               _loc3_.clear();
               if(_loc4_ == 0)
               {
                  _loc3_.part = this.m_mc.all_charlist_8.mc_namebar_00;
               }
               if(_loc4_ == 1)
               {
                  _loc3_.part = this.m_mc.all_charlist_8.mc_namebar_01;
               }
               if(_loc4_ == 2)
               {
                  _loc3_.part = this.m_mc.all_charlist_8.mc_namebar_02;
               }
               if(_loc4_ == 3)
               {
                  _loc3_.part = this.m_mc.all_charlist_8.mc_namebar_03;
               }
               if(_loc4_ == 4)
               {
                  _loc3_.part = this.m_mc.all_charlist_8.mc_namebar_04;
               }
               if(_loc4_ == 5)
               {
                  _loc3_.part = this.m_mc.all_charlist_8.mc_namebar_05;
               }
               if(_loc4_ == 6)
               {
                  _loc3_.part = this.m_mc.all_charlist_8.mc_namebar_06;
               }
               if(_loc4_ == 7)
               {
                  _loc3_.part = this.m_mc.all_charlist_8.mc_namebar_07;
               }
               this.setUser(_loc4_,_loc3_);
               _loc4_++;
            }
         }
         this.UpdateUser();
         this.AnmRefreshChara(-1,-1,false);
      }
      
      public function finalize() : void
      {
         var _loc1_:int = 0;
         while(_loc1_ < this.m_user_num)
         {
            if(Boolean(this.m_user) && Boolean(this.m_user[_loc1_]))
            {
               this.m_user[_loc1_].finalize();
            }
            _loc1_++;
         }
         if(this.keypush == true && Boolean(this.m_keyHelp))
         {
            this.m_keyHelp.PopKeyHelp();
            this.keypush = false;
         }
         if(this.m_isPushScroll)
         {
            if(this.m_first)
            {
               if(!this.m_net || this.m_guest == false)
               {
                  ExternalInterface.call("PopScrollHelp");
               }
            }
         }
      }
      
      public function init_borad() : void
      {
         if(this.m_user_num == CCD_TYPE_TOURNAMENT_ALLNUM_P4)
         {
            this.m_mc.all_board_4.mc_board_00.gotoAndStop("in");
            this.m_mc.all_board_4.mc_board_01.gotoAndStop("in");
            this.m_mc.all_board_4.mc_board_02.gotoAndStop("in");
            this.m_mc.all_board_4.mc_board_03.gotoAndStop("in");
            this.m_mc.all_board_4.mc_board_04.gotoAndStop("in");
            this.m_mc.all_board_4.mc_board_05.gotoAndStop("in");
            this.m_mc.all_board_4.mc_board_06.gotoAndStop("in");
            this.m_mc.all_charlist_8.visible = false;
            this.m_mc.all_board_8.visible = false;
         }
         else
         {
            this.m_mc.all_board_8.mc_board_00.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_01.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_02.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_03.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_04.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_05.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_06.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_07.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_08.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_09.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_10.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_11.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_12.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_13.gotoAndStop("in");
            this.m_mc.all_board_8.mc_board_14.gotoAndStop("in");
            this.m_mc.all_charlist_4.visible = false;
            this.m_mc.all_board_4.visible = false;
         }
      }
      
      public function DebugInit() : void
      {
      }
      
      public function Ctrl() : void
      {
         var _loc1_:int = 0;
         if(!this.isStart)
         {
            _loc1_ = 1;
            while(_loc1_ < this.m_user_num)
            {
               if(this.m_user[_loc1_].isLoad() == false)
               {
                  return;
               }
               _loc1_++;
            }
            if(this.m_mc.all_trop.currentFrameLabel != "loop")
            {
               return;
            }
            this.isStart = true;
            if(Boolean(this.m_keyHelp) && this.enableSetting)
            {
               if(this.m_net == true)
               {
                  if(this.m_first == false || this.m_guest == true)
                  {
                     return;
                  }
               }
            }
         }
         if(this.resultmode >= 1 && this.resultmode < 1000)
         {
            this.ModeCall(2);
            this.mode_ResultReflection_Anm();
         }
         else if(this.resultmode >= 1000 && this.resultmode < 2000)
         {
            this.ModeCall(1);
            this.mode_ResultReflection_Change();
         }
         else if(this.resultmode >= 2000 && this.resultmode < 3000)
         {
            this.ModeCall(0);
            this.mode_ResultReflection_Select();
         }
         else if(this.resultmode >= 3000 && this.resultmode < 4000)
         {
            this.ModeCall(3);
            this.mode_ResultReflection_AdvWait();
         }
      }
      
      public function ModeCall(param1:Number) : void
      {
         if(this.resultmode_log != param1)
         {
            this.resultmode_log = param1;
            if(this.CallSetMode != null)
            {
               this.CallSetMode(param1);
            }
         }
      }
      
      public function DebugCtrl() : void
      {
         if(this.m_inputPad.GetKeyInputBtn_R_Left() != this.m_inputPad.GetPadPress())
         {
            if(this.m_inputPad.GetKeyInputBtn_R_Up() != this.m_inputPad.GetPadPress())
            {
               if(this.m_inputPad.GetKeyInputBtn_R1() != this.m_inputPad.GetPadPress())
               {
                  if(this.m_inputPad.GetKeyInputBtn_R2() == this.m_inputPad.GetPadPress())
                  {
                     this.init();
                     this.dinit = false;
                     this.DebugInit();
                     this.mode_ResultReflection_SetAnmMatch();
                  }
                  else if(this.m_inputPad.GetKeyInputBtn_R_Down() == this.m_inputPad.GetPadPress())
                  {
                  }
               }
            }
         }
      }
      
      public function mode_ResultReflection_Anm() : *
      {
         var _loc3_:* = undefined;
         var _loc4_:* = undefined;
         var _loc5_:* = undefined;
         var _loc6_:Boolean = false;
         var _loc7_:Boolean = false;
         var _loc1_:int = 0;
         var _loc2_:int = 0;
         if(this.resultmode == 1)
         {
            if(this.resultcount > this.resultcountStop)
            {
               if(this.flag_steplast == false)
               {
                  this.flag_steplast = true;
                  if(this.CallStepAnmEnd != null)
                  {
                     this.CallStepAnmEnd(true);
                  }
                  if(this.resultcount > this.getAllGameNum())
                  {
                     this.resultmode = 200;
                  }
               }
            }
            else
            {
               _loc3_ = this.getPlayNo(this.resultcount,true);
               _loc4_ = this.getPlayNo(this.resultcount,false);
               _loc5_ = this.getResult();
               this.setResult(_loc5_,true);
               this.AnimAns = -1;
               if(_loc5_ == 1)
               {
                  this.AnimAns = this.getAnmNo(this.resultcount,true);
               }
               else if(_loc5_ == 2)
               {
                  this.AnimAns = this.getAnmNo(this.resultcount,false);
               }
               else
               {
                  if(_loc5_ == 0)
                  {
                     if(this.flag_steplast == false)
                     {
                        this.flag_steplast = true;
                        if(this.CallStepAnmEnd != null)
                        {
                           this.CallStepAnmEnd(true);
                        }
                     }
                     return;
                  }
                  if(_loc5_ == -2)
                  {
                     _loc6_ = true;
                     _loc7_ = true;
                     if(_loc3_ >= 0)
                     {
                        if(this.m_user[_loc3_].getVisible() == false || this.m_user[_loc3_].getDead() == true)
                        {
                           _loc7_ = false;
                        }
                     }
                     else
                     {
                        _loc7_ = false;
                     }
                     if(_loc4_ >= 0)
                     {
                        if(this.m_user[_loc4_].getVisible() == false || this.m_user[_loc4_].getDead() == true)
                        {
                           if(_loc7_ == false)
                           {
                              _loc6_ = false;
                           }
                        }
                     }
                     else if(this.resultcount >= this.getAllGameNum())
                     {
                        _loc6_ = true;
                     }
                     else if(_loc7_ == false)
                     {
                        _loc6_ = false;
                     }
                     if(_loc6_ == true)
                     {
                        this.AnimAns = this.getAnmNo(this.resultcount,_loc7_);
                     }
                  }
               }
               ++this.resultcount;
               if(this.AnimAns >= 0)
               {
                  this.resultmode = 10;
               }
               else
               {
                  this.resultmode = 100;
               }
            }
         }
         else if(this.resultmode == 10)
         {
            if(this.isEndAnmDead() == false)
            {
               return;
            }
            this.resultmodeAnm_mc = this.getAnmMc(this.AnimAns);
            if(this.resultmodeAnm_mc != null)
            {
               this.resultmodeAnm_mc.gotoAndPlay("in");
               this.resultmode = 15;
            }
            else
            {
               this.resultmode = 100;
            }
         }
         else if(this.resultmode == 15)
         {
            if(this.resultmodeAnm_mc != null)
            {
               if(this.resultmodeAnm_mc.currentFrameLabel == "loop")
               {
                  this.resultmode = 100;
               }
            }
            else
            {
               this.resultmode = 100;
            }
         }
         else if(this.resultmode == 100)
         {
            if(this.resultcount > this.getAllGameNum())
            {
               this.resultmode = 200;
            }
            else
            {
               this.resultmode = 1;
            }
         }
         else if(this.resultmode == 200)
         {
            if(!this.flag_last)
            {
               ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_TENSION_UP);
            }
            this.flag_last = true;
            if(this.CallStepFinish != null)
            {
               this.CallStepFinish(true);
            }
         }
      }
      
      public function mode_ResultReflection_SetAnmMatch() : *
      {
         var _loc2_:* = undefined;
         var _loc3_:* = undefined;
         var _loc4_:* = undefined;
         var _loc5_:* = undefined;
         var _loc6_:Boolean = false;
         var _loc7_:Boolean = false;
         var _loc1_:int = 0;
         _loc1_ = 0;
         while(_loc1_ <= this.resultcountStop)
         {
            _loc2_ = this.getPlayNo(this.resultcount,true);
            _loc3_ = this.getPlayNo(this.resultcount,false);
            _loc4_ = this.getResult();
            _loc5_ = -1;
            this.setResult(_loc4_,false);
            if(_loc4_ == 1)
            {
               _loc5_ = this.getAnmNo(this.resultcount,true);
            }
            else if(_loc4_ == 2)
            {
               _loc5_ = this.getAnmNo(this.resultcount,false);
            }
            else
            {
               if(_loc4_ == 0)
               {
                  break;
               }
               if(_loc4_ != -1)
               {
                  if(_loc4_ == -2)
                  {
                     _loc6_ = true;
                     _loc7_ = true;
                     if(_loc2_ >= 0)
                     {
                        if(this.m_user[_loc2_].getVisible() == false || this.m_user[_loc2_].getDead() == true)
                        {
                           _loc7_ = false;
                        }
                     }
                     else
                     {
                        _loc7_ = false;
                     }
                     if(_loc3_ >= 0)
                     {
                        if(this.m_user[_loc3_].getVisible() == false || this.m_user[_loc3_].getDead() == true)
                        {
                           if(_loc2_ == -1)
                           {
                              if(this.resultcount < this.getAllGameNum())
                              {
                                 _loc6_ = false;
                              }
                           }
                           else if(_loc7_ == false)
                           {
                              _loc6_ = false;
                           }
                        }
                     }
                     else if(this.resultcount >= this.getAllGameNum())
                     {
                        _loc6_ = true;
                     }
                     else if(_loc7_ == false)
                     {
                        _loc6_ = false;
                     }
                     if(_loc6_ == true)
                     {
                        _loc5_ = this.getAnmNo(this.resultcount,_loc7_);
                     }
                  }
               }
            }
            if(_loc5_ >= 0)
            {
               this.resultmodeAnm_mc = this.getAnmMc(_loc5_);
               if(this.resultmodeAnm_mc != null)
               {
                  this.resultmodeAnm_mc.gotoAndStop("loop");
               }
            }
            ++this.resultcount;
            _loc1_++;
         }
      }
      
      public function mode_ResultReflection_Select() : *
      {
         var _loc2_:Boolean = false;
         var _loc3_:int = 0;
         var _loc4_:Boolean = false;
         var _loc5_:int = 0;
         var _loc6_:Array = null;
         var _loc7_:int = 0;
         var _loc8_:Array = null;
         var _loc9_:int = 0;
         var _loc1_:int = -1;
         if(this.resultmode == 2000)
         {
            if(this.m_net == true)
            {
               this.AnmRefreshChara(-1,-1,false);
            }
            else
            {
               this.AnmRefreshChara(1,-1,false);
            }
            if(this.m_guest == true || this.m_first == false)
            {
               this.resultmode = 2001;
            }
            else
            {
               if(this.m_keyHelp)
               {
                  if(this.keypush == true)
                  {
                     this.m_keyHelp.PopKeyHelp();
                     this.keypush = false;
                  }
                  this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_R1,"tournament_030");
                  if(this.m_net == false)
                  {
                     this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_R_LEFT,"tournament_031");
                  }
                  this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_R_UP,"MSG_RandomSel");
                  if(this.m_net == false)
                  {
                     this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
                  }
                  this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_NEXT);
                  this.m_keyHelp.PushKeyHelp();
                  this.keypush = true;
               }
               this.resultmode = 2001;
               if(this.m_first)
               {
                  if(!this.m_net || this.m_guest == false)
                  {
                     if(!this.m_isPushScroll)
                     {
                        ExternalInterface.call("PushScrollHelp");
                        this.m_isPushScroll = true;
                     }
                     ExternalInterface.call("SetScrollHelpId","tournament_010");
                  }
               }
               this.m_select1.SetSelValue(1);
               this.m_select_no = this.m_select1.GetSelValue();
            }
            if(this.m_net == false)
            {
               _loc2_ = false;
               _loc3_ = 0;
               if(this.m_user)
               {
                  _loc3_ = 1;
                  while(_loc3_ < this.m_user_num)
                  {
                     if(this.m_user[_loc3_].cpu == false)
                     {
                        _loc2_ = true;
                        break;
                     }
                     _loc3_++;
                  }
               }
               if(!this.enable2pController && _loc2_)
               {
                  this.m_mc.all_credit.visible = true;
                  this.m_mc.all_credit.gotoAndPlay("in");
                  this.CallRequest2pController(true);
               }
            }
         }
         else if(this.resultmode == 2001)
         {
            if(this.m_net == false)
            {
               this.CharaPanelSelect(-1);
               if(this.m_select_no >= 0)
               {
                  if(this.m_inputPad.GetKeyInputBtn_R_Left() == this.m_inputPad.GetPadPress())
                  {
                     if(this.m_user[this.m_select_no].cpu == false)
                     {
                        this.ChangeId(this.m_select_no,true);
                        this.m_user[this.m_select_no].cpu = true;
                     }
                     else
                     {
                        this.ChangeId(this.m_select_no,false);
                        this.m_user[this.m_select_no].cpu = false;
                     }
                     this.m_user[this.m_select_no].updata_mc();
                     _loc4_ = false;
                     if(!this.enable2pController)
                     {
                        _loc5_ = 1;
                        while(_loc5_ < this.m_user_num)
                        {
                           if(this.m_user[_loc5_].cpu == false)
                           {
                              _loc4_ = true;
                              break;
                           }
                           _loc5_++;
                        }
                        if(_loc4_ && !this.m_mc.all_credit.visible)
                        {
                           this.m_mc.all_credit.visible = true;
                           this.m_mc.all_credit.gotoAndPlay("in");
                           this.CallRequest2pController(true);
                        }
                        else if(!_loc4_ && Boolean(this.m_mc.all_credit.visible))
                        {
                           this.m_mc.all_credit.visible = false;
                           this.CallRequest2pController(false);
                        }
                     }
                     ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MENU_SELECT);
                  }
                  else if(this.m_inputPad.GetKeyInputBtn_Cancel() == this.m_inputPad.GetPadPress())
                  {
                     if(this.m_net == false)
                     {
                        this.CallCancel();
                        ExternalInterface.call("RequestPlaySE_Cancel");
                     }
                  }
               }
               if(this.m_inputPad.GetKeyInputBtn_R_Up() == this.m_inputPad.GetPadPress())
               {
                  _loc6_ = new Array();
                  _loc7_ = 0;
                  while(_loc7_ < this.m_user_num)
                  {
                     _loc6_.push(this.m_user[_loc7_].id);
                     _loc7_++;
                  }
                  this.CallFixPlayer(_loc6_);
                  this.CallShufflePlayer();
                  ExternalInterface.call("RequestPlaySE_Fix");
               }
            }
         }
         if(this.m_net == true)
         {
            if(this.m_inputPad.GetKeyInputBtn_R_Up() == this.m_inputPad.GetPadPress())
            {
               this.isAllChange = true;
            }
         }
         if(this.m_inputPad.GetKeyInputBtn_R1() == this.m_inputPad.GetPadPress())
         {
            this.resultmode = 1000;
            if(this.m_keyHelp)
            {
               if(this.keypush == true)
               {
                  this.m_keyHelp.PopKeyHelp();
                  this.keypush = false;
               }
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
               this.m_keyHelp.AddKeyHelpId(KeyHelpCode.CCD_BTN_ICON_OK,"tournament_030");
               this.m_keyHelp.PushKeyHelp();
               this.keypush = true;
            }
            if(this.m_first)
            {
               if(!this.m_net || this.m_guest == false)
               {
                  ExternalInterface.call("SetScrollHelpId","tournament_011");
               }
            }
            ExternalInterface.call("RequestPlaySE_Fix");
         }
         if(this.m_guest == true || this.m_first == false)
         {
            this.setAnmSelect(-1,-1);
            this.resultmode = 1;
            return;
         }
         if(this.m_inputPad.GetKeyInputBtn_Ok() == this.m_inputPad.GetPadPress() || this.m_skip == true)
         {
            if(!this.m_mc.all_credit.visible)
            {
               this.setAnmSelect(-1,-1);
               this.resultmode = 1;
               if(this.m_skip == false)
               {
                  ExternalInterface.call("RequestPlaySE_Fix");
               }
               if(!this.m_net)
               {
                  _loc8_ = new Array();
                  _loc9_ = 0;
                  while(_loc9_ < this.m_user_num)
                  {
                     if(this.m_user[_loc9_].cpu)
                     {
                        _loc8_.push(int(8));
                     }
                     else
                     {
                        _loc8_.push(this.m_user[_loc9_].id);
                     }
                     _loc9_++;
                  }
                  this.CallFixPlayer(_loc8_);
               }
               if(this.m_keyHelp)
               {
                  if(this.keypush == true)
                  {
                     this.m_keyHelp.PopKeyHelp();
                     this.keypush = false;
                  }
               }
            }
         }
      }
      
      public function mode_ResultReflection_AdvWait() : *
      {
         if(this.resultmode == 3000)
         {
            this.AnmRefreshChara(-1,-1,false);
            if(this.m_keyHelp)
            {
               if(this.keypush == true)
               {
                  this.m_keyHelp.PopKeyHelp();
                  this.keypush = false;
               }
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_NEXT);
               this.m_keyHelp.PushKeyHelp();
               this.keypush = true;
            }
            this.resultmode = 3001;
         }
         else if(this.resultmode == 3001)
         {
            if(this.m_inputPad.GetKeyInputBtn_Ok() == this.m_inputPad.GetPadPress())
            {
               this.setAnmSelect(-1,-1);
               this.resultmode = 1;
               if(this.m_keyHelp)
               {
                  if(this.keypush == true)
                  {
                     this.m_keyHelp.PopKeyHelp();
                     this.keypush = false;
                  }
               }
            }
         }
      }
      
      public function mode_ResultReflection_Change() : *
      {
         var _loc1_:int = -1;
         if(this.resultmode == 1000)
         {
            this.mode_Change_1 = -1;
            this.mode_Change_2 = -1;
            this.resultmode = 1001;
            if(this.m_first)
            {
               if(!this.m_net || this.m_guest == false)
               {
                  ExternalInterface.call("SetScrollHelpId","tournament_011");
               }
            }
         }
         else if(this.resultmode == 1001)
         {
            if(this.mode_Change_1 >= 0)
            {
               this.m_select_no = this.mode_Change_1;
            }
            if(this.m_select_no == 0)
            {
               this.m_select_no = 1;
            }
            this.setAnmSelect(this.m_select_no,-1);
            this.resultmode = 1010;
         }
         else if(this.resultmode == 1010)
         {
            _loc1_ = this.CharaPanelSelect(-1);
            if(_loc1_ >= 0)
            {
               this.mode_Change_1 = _loc1_;
            }
            if(this.mode_Change_1 >= 0)
            {
               if(this.m_inputPad.GetKeyInputBtn_Ok() == this.m_inputPad.GetPadPress() && this.m_skip == false)
               {
                  this.setAnmSelect(this.m_select_no,this.mode_Change_1);
                  this.resultmode = 1020;
                  ExternalInterface.call("RequestPlaySE_Fix");
                  if(this.m_first)
                  {
                     if(!this.m_net || this.m_guest == false)
                     {
                        ExternalInterface.call("SetScrollHelpId","tournament_012");
                     }
                  }
               }
            }
            if(this.m_inputPad.GetKeyInputBtn_Cancel() == this.m_inputPad.GetPadPress() || this.m_skip == true)
            {
               this.resultmode = 2000;
               if(this.m_skip == false)
               {
                  ExternalInterface.call("RequestPlaySE_Cancel");
               }
            }
         }
         else if(this.resultmode == 1020)
         {
            _loc1_ = this.CharaPanelSelect(this.mode_Change_1);
            if(_loc1_ >= 0)
            {
               this.mode_Change_2 = _loc1_;
            }
            if(this.mode_Change_2 != this.mode_Change_1 && this.mode_Change_2 >= 0)
            {
               if(this.m_inputPad.GetKeyInputBtn_Ok() == this.m_inputPad.GetPadPress() && this.m_skip == false)
               {
                  this.resultmode = 1030;
                  ExternalInterface.call("RequestPlaySE_Fix");
               }
            }
            if(this.m_inputPad.GetKeyInputBtn_Cancel() == this.m_inputPad.GetPadPress() || this.m_skip == true)
            {
               this.setAnmSelect(this.m_select_no,-1);
               this.mode_Change_2 = -1;
               this.resultmode = 1010;
               if(this.m_first)
               {
                  if(!this.m_net || this.m_guest == false)
                  {
                     ExternalInterface.call("SetScrollHelpId","tournament_011");
                  }
               }
               if(this.m_skip == false)
               {
                  ExternalInterface.call("RequestPlaySE_Cancel");
               }
            }
         }
         else if(this.resultmode >= 1030 && this.resultmode < 1040)
         {
            this.mode_ResultReflection_Change_Anm();
         }
      }
      
      public function mode_ResultReflection_Change_Anm() : *
      {
         if(this.resultmode == 1030)
         {
            this.setChangeUset(this.mode_Change_1,this.mode_Change_2);
            if(this.m_net == false)
            {
               this.CallSwapPlayer(this.mode_Change_1,this.mode_Change_2);
            }
            this.resultmode = 1031;
         }
         else if(this.resultmode == 1031)
         {
            this.AnmChangeUser();
            if(this.isEndAnmChangeUser() == true)
            {
               this.resultmode = 1000;
            }
         }
      }
      
      public function setMovieClip(param1:MovieClip) : void
      {
         this.m_mc = param1;
      }
      
      public function setUserNum(param1:int) : void
      {
         this.m_user_num = param1;
         if(this.m_user_num == CCD_TYPE_TOURNAMENT_ALLNUM_P4)
         {
            if(this.m_select1 != null)
            {
               this.m_select1.SetMinValue(1);
               this.m_select1.SetMaxValue(3);
            }
         }
         else if(this.m_user_num == CCD_TYPE_TOURNAMENT_ALLNUM_P8)
         {
            if(this.m_select1 != null)
            {
               this.m_select1.SetMinValue(1);
               this.m_select1.SetMaxValue(7);
            }
         }
      }
      
      public function setUser(param1:int, param2:tournament_member) : void
      {
         if(Boolean(this.m_user) && Boolean(param2))
         {
            param2.isNet = this.m_net;
            if(param2.part != null)
            {
               this.m_user[param1].setUser(param2);
            }
            else
            {
               this.m_user[param1].setUserData(param2);
            }
            this.m_user[param1].AnmSelect(false,false);
         }
      }
      
      public function UpdateUser() : void
      {
         var _loc1_:int = 0;
         if(this.m_user)
         {
            _loc1_ = 0;
            while(_loc1_ < this.m_user_num)
            {
               this.m_user[_loc1_].updata_mc();
               _loc1_++;
            }
         }
      }
      
      public function UpdateUser2(param1:int) : void
      {
         this.m_user[param1].updata_mc();
      }
      
      public function getResult() : int
      {
         var _loc1_:int = 0;
         var _loc2_:int = this.getPlayNo(this.resultcount,true);
         var _loc3_:int = this.getPlayNo(this.resultcount,false);
         var _loc4_:int = 0;
         if(this.resultcount >= this.getAllGameNum())
         {
            _loc4_ = -2;
         }
         else if(this.getLiveOne() == true)
         {
            _loc4_ = -2;
         }
         else if(_loc2_ < 0 || _loc3_ < 0)
         {
            if(_loc2_ < 0 && _loc3_ < 0)
            {
               _loc4_ = -1;
            }
            else if(_loc2_ < 0)
            {
               _loc4_ = 2;
            }
            else if(_loc3_ < 0)
            {
               _loc4_ = 1;
            }
         }
         else if(this.m_user[_loc2_].getVisible() == false && this.m_user[_loc3_].getVisible() == false)
         {
            _loc4_ = -1;
         }
         else if(this.m_user[_loc2_].getVisible() == true && this.m_user[_loc3_].getVisible() == false)
         {
            _loc4_ = 1;
         }
         else if(this.m_user[_loc2_].getVisible() == false && this.m_user[_loc3_].getVisible() == true)
         {
            _loc4_ = 2;
         }
         else if(this.m_user[_loc2_].getDead() == true && this.m_user[_loc3_].getDead() == true)
         {
            _loc4_ = -1;
         }
         else if(this.m_user[_loc2_].getWin() <= 0 && this.m_user[_loc3_].getWin() <= 0)
         {
            _loc4_ = 0;
         }
         else if(this.m_user[_loc2_].getWin() > 0 && this.m_user[_loc3_].getWin() > 0)
         {
            this.m_user[_loc2_].setWin();
            this.m_user[_loc3_].setWin();
         }
         else if(this.m_user[_loc2_].getWin() > 0)
         {
            _loc4_ = 1;
         }
         else if(this.m_user[_loc3_].getWin() > 0)
         {
            _loc4_ = 2;
         }
         if(_loc4_ == 1)
         {
            if(_loc2_ >= 0)
            {
               if(this.m_user[_loc2_].getWin() <= 0)
               {
                  if(_loc3_ >= 0)
                  {
                     if(this.m_user[_loc3_].getChara() != "")
                     {
                        _loc4_ = -1;
                     }
                  }
               }
            }
         }
         if(_loc4_ == 2)
         {
            if(_loc3_ >= 0)
            {
               if(this.m_user[_loc3_].getWin() <= 0)
               {
                  if(_loc2_ >= 0)
                  {
                     if(this.m_user[_loc2_].getChara() != "")
                     {
                        _loc4_ = -1;
                     }
                  }
               }
            }
         }
         return _loc4_;
      }
      
      public function setResult(param1:int, param2:Boolean) : void
      {
         var _loc3_:* = this.getResult();
         var _loc4_:* = this.getPlayNo(this.resultcount,true);
         var _loc5_:* = this.getPlayNo(this.resultcount,false);
         if(param1 == 1)
         {
            this.setResult_WinUser(_loc4_);
            this.setResult_DeadUser(_loc5_,param2);
         }
         else if(param1 == 2)
         {
            this.setResult_WinUser(_loc5_);
            this.setResult_DeadUser(_loc4_,param2);
         }
         else
         {
            if(param1 == 0)
            {
               return;
            }
            if(param1 == -1)
            {
               this.setResult_DeadUser(_loc4_,param2);
               this.setResult_DeadUser(_loc5_,param2);
            }
            else if(param1 == -2)
            {
            }
         }
      }
      
      private function setResult_WinUser(param1:int) : void
      {
         if(param1 >= 0)
         {
            this.m_user[param1].setWin();
         }
      }
      
      private function setResult_DeadUser(param1:int, param2:Boolean) : void
      {
         if(param1 >= 0)
         {
            this.m_user[param1].setDead(true);
            this.m_user[param1].AnmDead(param2);
            this.DeadUser = param1;
            if(param2)
            {
               ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_CATCH_NG);
            }
         }
      }
      
      public function isEndAnmDead() : Boolean
      {
         if(this.DeadUser < 0)
         {
            return true;
         }
         if(this.m_user)
         {
            if(this.m_user[this.DeadUser].part)
            {
               if(this.m_user[this.DeadUser].part.isEndDark() == false)
               {
                  return false;
               }
            }
         }
         this.DeadUser = -1;
         return true;
      }
      
      public function getLiveOne() : Boolean
      {
         var _loc1_:int = 0;
         var _loc2_:int = this.m_user_num;
         var _loc3_:int = 0;
         var _loc4_:Boolean = false;
         _loc1_ = 0;
         while(_loc1_ < _loc2_)
         {
            if(this.m_user[_loc1_].getVisible() == true && this.m_user[_loc1_].getDead() == false)
            {
               _loc3_++;
            }
            _loc1_++;
         }
         if(_loc3_ <= 1)
         {
            _loc4_ = true;
         }
         return _loc4_;
      }
      
      public function getPlayNo(param1:int, param2:Boolean) : int
      {
         if(this.m_user_num == CCD_TYPE_TOURNAMENT_ALLNUM_P4)
         {
            if(param1 == 0)
            {
               if(param2 == true)
               {
                  return 0;
               }
               return 1;
            }
            if(param1 == 1)
            {
               if(param2 == true)
               {
                  return 2;
               }
               return 3;
            }
            if(param1 == 2)
            {
               if(param2 == true)
               {
                  return this.getPlayNo_Sub(0,1);
               }
               return this.getPlayNo_Sub(2,3);
            }
         }
         else
         {
            if(param1 == 0)
            {
               if(param2 == true)
               {
                  return 0;
               }
               return 1;
            }
            if(param1 == 1)
            {
               if(param2 == true)
               {
                  return 2;
               }
               return 3;
            }
            if(param1 == 2)
            {
               if(param2 == true)
               {
                  return 4;
               }
               return 5;
            }
            if(param1 == 3)
            {
               if(param2 == true)
               {
                  return 6;
               }
               return 7;
            }
            if(param1 == 4)
            {
               if(param2 == true)
               {
                  return this.getPlayNo_Sub(0,1);
               }
               return this.getPlayNo_Sub(2,3);
            }
            if(param1 == 5)
            {
               if(param2 == true)
               {
                  return this.getPlayNo_Sub(4,5);
               }
               return this.getPlayNo_Sub(6,7);
            }
            if(param1 == 6)
            {
               if(param2 == true)
               {
                  return this.getPlayNo_Sub(0,3);
               }
               return this.getPlayNo_Sub(4,7);
            }
         }
         return -1;
      }
      
      public function getPlayNo_Sub(param1:int, param2:int) : *
      {
         var _loc3_:int = param1;
         while(_loc3_ <= param2)
         {
            if(this.m_user[_loc3_].getDead() == false)
            {
               return _loc3_;
            }
            _loc3_++;
         }
         return -1;
      }
      
      public function setPlayerDead(param1:int) : *
      {
         this.m_user[param1].setDead(true);
      }
      
      public function getAllGameNum() : int
      {
         if(this.m_user_num == CCD_TYPE_TOURNAMENT_ALLNUM_P4)
         {
            return CCD_TYPE_TOURNAMENT_RESULTENUM_P4;
         }
         return CCD_TYPE_TOURNAMENT_RESULTENUM_P8;
      }
      
      public function setAnmSelect(param1:int, param2:int) : void
      {
         var _loc3_:int = 0;
         while(_loc3_ < this.getAllMemberNum())
         {
            if(this.m_user[_loc3_].getVisible() == false)
            {
               this.m_user[_loc3_].AnmDead(false);
            }
            else if(this.m_user[_loc3_].getDead() == false)
            {
               if(_loc3_ != param2)
               {
                  this.m_user[_loc3_].AnmSelect(false,false);
               }
               else
               {
                  this.m_user[_loc3_].AnmSelect(true,false);
               }
            }
            _loc3_++;
         }
         if(param1 >= 0)
         {
            if(this.m_user[param1].getDead() == false)
            {
               if(param2 == param1)
               {
                  this.m_user[param1].AnmSelect(true,true);
               }
               else
               {
                  this.m_user[param1].AnmSelect(false,true);
               }
            }
         }
      }
      
      public function getAllMemberNum() : int
      {
         return this.m_user_num;
      }
      
      public function setChangeUset(param1:int, param2:int) : *
      {
         this.Change_mode = 0;
         this.Change_no1 = param1;
         this.Change_no2 = param2;
      }
      
      public function AnmChangeUser() : *
      {
         var _loc2_:tournament_member = null;
         var _loc3_:* = undefined;
         var _loc4_:* = undefined;
         var _loc1_:Number = 0;
         if(this.Change_mode == 0)
         {
            _loc1_ = Number(this.m_user[this.Change_no1].part.alpha);
            _loc1_ -= 0.05;
            if(_loc1_ < 0)
            {
               _loc1_ = 0;
               this.Change_mode = 10;
            }
            this.m_user[this.Change_no1].part.alpha = _loc1_;
            this.m_user[this.Change_no2].part.alpha = _loc1_;
         }
         else if(this.Change_mode == 10)
         {
            _loc2_ = new tournament_member();
            _loc2_.setUserData(this.m_user[this.Change_no1]);
            _loc3_ = this.m_user[this.Change_no1].getID();
            _loc4_ = this.m_user[this.Change_no2].getID();
            this.m_user[this.Change_no1].setUserData(this.m_user[this.Change_no2]);
            this.m_user[this.Change_no2].setUserData(_loc2_);
            if(this.m_net == true)
            {
               this.m_user[this.Change_no1].setID(_loc3_);
               this.m_user[this.Change_no2].setID(_loc4_);
            }
            this.m_user[this.Change_no1].AnmSelect(false,false);
            this.m_user[this.Change_no1].updata_mc();
            this.m_user[this.Change_no2].updata_mc();
            this.Change_mode = 20;
         }
         else if(this.Change_mode == 20)
         {
            _loc1_ = Number(this.m_user[this.Change_no1].part.alpha);
            _loc1_ += 0.05;
            if(_loc1_ >= 1)
            {
               _loc1_ = 1;
               this.Change_mode = -1;
            }
            this.m_user[this.Change_no1].part.alpha = _loc1_;
            this.m_user[this.Change_no2].part.alpha = _loc1_;
         }
      }
      
      public function isEndAnmChangeUser() : Boolean
      {
         if(this.Change_mode < 0)
         {
            return true;
         }
         return false;
      }
      
      public function AnmRefreshChara(param1:int, param2:int, param3:Boolean) : void
      {
         var _loc4_:int = 0;
         while(_loc4_ < this.getAllMemberNum())
         {
            if(this.m_user[_loc4_].getVisible() == false)
            {
               this.m_user[_loc4_].AnmDead(false);
            }
            else if(this.m_user[_loc4_].getDead() == false)
            {
               if(_loc4_ != param2)
               {
                  this.m_user[_loc4_].part.setSelect(false,false);
               }
               else
               {
                  this.m_user[_loc4_].part.setSelect(true,false);
               }
            }
            else
            {
               this.m_user[_loc4_].part.setDark(true,true);
            }
            _loc4_++;
         }
         if(param1 >= 0)
         {
            if(this.m_user[param1].getVisible() == false)
            {
               this.m_user[param1].AnmDead(false);
            }
            else if(this.m_user[param1].getDead() == false)
            {
               this.m_user[param1].part.setSelect(false,true);
            }
            else
            {
               this.m_user[param1].part.setDark(param3,true);
            }
         }
      }
      
      public function CharaPanelSelect(param1:int) : int
      {
         var _loc2_:* = 0;
         var _loc3_:int = 0;
         if(this.m_select1 == null)
         {
            return -1;
         }
         if(this.m_select1 != null)
         {
            this.m_select1.SelectMenuCtrl();
            _loc3_ = this.m_select1.GetSelValue();
         }
         if(_loc3_ != this.m_select_no)
         {
            if(this.m_user[_loc3_].getDead() == true || this.m_user[_loc3_].getVisible() == false)
            {
               if(this.m_select_no < _loc3_)
               {
                  _loc2_ = _loc3_;
                  while(_loc2_ < this.getAllMemberNum())
                  {
                     if(!(this.m_user[_loc2_].getDead() == true && this.m_user[_loc2_].getLock() == false && this.m_user[_loc2_].getVisible() == false))
                     {
                        this.m_select1.SetSelValue(_loc2_);
                        _loc3_ = _loc2_;
                        break;
                     }
                     if(_loc2_ + 1 == this.getAllMemberNum())
                     {
                        this.m_select1.SetSelValue(this.m_select_no);
                        _loc3_ = this.m_select_no;
                        break;
                     }
                     _loc2_++;
                  }
               }
               else if(this.m_select_no > _loc3_)
               {
                  _loc2_ = _loc3_;
                  while(_loc2_ >= 0)
                  {
                     if(!(this.m_user[_loc2_].getDead() == true && this.m_user[_loc2_].getLock() == false && this.m_user[_loc2_].getVisible() == false))
                     {
                        this.m_select1.SetSelValue(_loc2_);
                        _loc3_ = _loc2_;
                        break;
                     }
                     if(_loc2_ - 1 == -1)
                     {
                        this.m_select1.SetSelValue(this.m_select_no);
                        _loc3_ = this.m_select_no;
                        break;
                     }
                     _loc2_--;
                  }
               }
            }
            this.m_select_no = _loc3_;
            this.setAnmSelect(this.m_select_no,param1);
            ExternalInterface.call("RequestPlaySE_Select");
            return this.m_select_no;
         }
         return this.m_select_no;
      }
      
      public function AddPlayerWin(param1:int) : void
      {
         var _loc2_:int = 0;
         var _loc3_:int = -1;
         if(this.m_net == true)
         {
            _loc3_ = param1;
         }
         else
         {
            _loc2_ = 0;
            while(_loc2_ < this.getAllMemberNum())
            {
               if(this.m_user[_loc2_].id == param1)
               {
                  _loc3_ = _loc2_;
                  break;
               }
               _loc2_++;
            }
            if(_loc3_ == -1)
            {
               trace("[error]:AddPlayerWin not found " + param1);
               return;
            }
         }
         this.flag_steplast = false;
         this.m_user[_loc3_].AddWin();
      }
      
      public function AddPlayerWinIndex(param1:int) : void
      {
         this.flag_steplast = false;
         this.m_user[param1].AddWin();
      }
      
      public function DebugWinSelect() : *
      {
      }
      
      public function getAnmNo(param1:int, param2:Boolean) : *
      {
         var _loc3_:int = param1 * 2;
         if(param1 < this.getAllGameNum())
         {
            if(param2)
            {
               return _loc3_;
            }
            return _loc3_ + 1;
         }
         return this.getAllGameNum() * 2;
      }
      
      public function getAnmMc(param1:int) : MovieClip
      {
         var _loc3_:MovieClip = null;
         var _loc2_:MovieClip = null;
         if(this.m_user_num == CCD_TYPE_TOURNAMENT_ALLNUM_P4)
         {
            _loc2_ = this.m_mc.all_board_4;
         }
         else
         {
            _loc2_ = this.m_mc.all_board_8;
         }
         if(_loc2_ != null)
         {
            _loc3_ = null;
            if(param1 == 0)
            {
               _loc3_ = _loc2_.mc_board_00;
            }
            if(param1 == 1)
            {
               _loc3_ = _loc2_.mc_board_01;
            }
            if(param1 == 2)
            {
               _loc3_ = _loc2_.mc_board_02;
            }
            if(param1 == 3)
            {
               _loc3_ = _loc2_.mc_board_03;
            }
            if(param1 == 4)
            {
               _loc3_ = _loc2_.mc_board_04;
            }
            if(param1 == 5)
            {
               _loc3_ = _loc2_.mc_board_05;
            }
            if(param1 == 6)
            {
               _loc3_ = _loc2_.mc_board_06;
            }
            if(param1 == 7)
            {
               _loc3_ = _loc2_.mc_board_07;
            }
            if(param1 == 8)
            {
               _loc3_ = _loc2_.mc_board_08;
            }
            if(param1 == 9)
            {
               _loc3_ = _loc2_.mc_board_09;
            }
            if(param1 == 10)
            {
               _loc3_ = _loc2_.mc_board_10;
            }
            if(param1 == 11)
            {
               _loc3_ = _loc2_.mc_board_11;
            }
            if(param1 == 12)
            {
               _loc3_ = _loc2_.mc_board_12;
            }
            if(param1 == 13)
            {
               _loc3_ = _loc2_.mc_board_13;
            }
            if(param1 == 14)
            {
               _loc3_ = _loc2_.mc_board_14;
            }
            if(_loc3_ != null)
            {
               return _loc3_;
            }
         }
         return null;
      }
      
      public function SetStageProgressMatch(param1:int) : void
      {
         if(this.m_user_num == CCD_TYPE_TOURNAMENT_ALLNUM_P4)
         {
            if(param1 == 0)
            {
               this.SetProgressMatch(0);
            }
            if(param1 == 1)
            {
               this.SetProgressMatch(1);
            }
            if(param1 == 2)
            {
               this.SetProgressMatch(99);
            }
         }
         else
         {
            if(param1 == 0)
            {
               this.SetProgressMatch(0);
            }
            if(param1 == 1)
            {
               this.SetProgressMatch(3);
            }
            if(param1 == 2)
            {
               this.SetProgressMatch(5);
            }
            if(param1 == 3)
            {
               this.SetProgressMatch(99);
            }
         }
      }
      
      public function SetSkipSetting() : void
      {
         this.resultmode = 1;
         this.enableSetting = false;
      }
      
      public function SetModeSorting() : void
      {
         this.resultmode = 1000;
      }
      
      public function SetProgressMatch(param1:int) : void
      {
         this.flag_steplast = false;
         this.resultcountStop = param1;
      }
      
      public function playProgressMatch() : void
      {
         this.flag_steplast = false;
         ++this.resultcountStop;
      }
      
      public function playProgressLastMatch() : void
      {
         this.flag_steplast = false;
         this.resultcountStop = 99;
      }
      
      public function playProgressNowMatch() : void
      {
         this.mode_ResultReflection_SetAnmMatch();
      }
      
      public function ChangeId(param1:Number, param2:Boolean) : *
      {
         var _loc3_:int = 0;
         var _loc4_:int = 0;
         var _loc5_:int = 0;
         if(param2)
         {
            this.m_user[param1].id = 8;
         }
         else
         {
            _loc3_ = 0;
            _loc4_ = 0;
            while(_loc4_ < this.getAllMemberNum())
            {
               _loc5_ = 0;
               while(_loc5_ < this.getAllMemberNum())
               {
                  if(this.m_user[_loc5_].cpu == false)
                  {
                     if(this.m_user[_loc5_].id == _loc3_)
                     {
                        _loc3_++;
                        break;
                     }
                  }
                  _loc5_++;
               }
               _loc4_++;
            }
            this.m_user[param1].id = _loc3_;
         }
      }
      
      public function setChangePlayerNo(param1:int, param2:int) : *
      {
         this.m_user[param1].cpu = false;
         this.m_user[param1].id = param2;
         this.m_user[param1].updata_mc();
      }
      
      public function getPlayerNo(param1:int) : int
      {
         var _loc2_:int = 0;
         while(_loc2_ < this.getAllMemberNum())
         {
            if(this.m_user[_loc2_].getID() == param1)
            {
               return _loc2_;
            }
            _loc2_++;
         }
         return -1;
      }
      
      public function getPlayerID(param1:int) : int
      {
         if(param1 >= 0 && param1 < this.getAllMemberNum())
         {
            return this.m_user[param1].getID();
         }
         return -1;
      }
      
      public function getPlayerEnterNo(param1:int) : int
      {
         if(param1 >= 0 && param1 < this.getAllMemberNum())
         {
            return this.m_user[param1].getEnterNo();
         }
         return -1;
      }
      
      public function getAllChange() : Boolean
      {
         var _loc1_:Boolean = this.isAllChange;
         this.isAllChange = false;
         return _loc1_;
      }
      
      public function SetGuset(param1:Boolean) : void
      {
         this.m_guest = param1;
      }
      
      public function SetFirst(param1:Boolean) : void
      {
         this.m_first = param1;
      }
      
      public function SetNetwork(param1:Boolean) : void
      {
         this.m_net = param1;
         var _loc2_:int = 0;
         if(this.m_user)
         {
            _loc2_ = 0;
            while(_loc2_ < this.m_user_num)
            {
               this.m_user[_loc2_].isNet = param1;
               _loc2_++;
            }
         }
      }
      
      public function IsNetwork() : Boolean
      {
         return this.m_net;
      }
      
      public function SetSpecial(param1:Boolean) : void
      {
         this.isSpecial = param1;
      }
      
      public function SetEnable2pController(param1:Boolean) : void
      {
         this.enable2pController = param1;
         this.m_mc.all_credit.visible = false;
      }
      
      public function ReplayStartAnm() : *
      {
         this.isStart = false;
         this.resultmode = 2000;
         if(this.m_keyHelp)
         {
            if(this.keypush == true)
            {
               this.m_keyHelp.PopKeyHelp();
               this.keypush = false;
            }
         }
         this.m_mc.all_title.gotoAndPlay("in");
         this.m_mc.all_trop.gotoAndPlay("in");
         if(this.m_user_num == CCD_TYPE_TOURNAMENT_ALLNUM_P4)
         {
            this.m_mc.all_charlist_4.gotoAndPlay("in");
            this.m_mc.all_board_4.gotoAndPlay("in");
         }
         else
         {
            this.m_mc.all_charlist_8.gotoAndPlay("in");
            this.m_mc.all_board_8.gotoAndPlay("in");
         }
         if(this.m_net == true)
         {
            this.AnmRefreshChara(-1,-1,false);
         }
         else
         {
            this.AnmRefreshChara(1,-1,false);
            this.m_select1.SetSelValue(1);
         }
      }
      
      public function SetAdvMode() : *
      {
         this.resultmode = 3000;
         var _loc1_:MovieClip = this.m_mc.all_title.getChildByName("mc_title") as MovieClip;
         if(_loc1_ != null)
         {
            _loc1_.gotoAndStop("freebtl_tmnt");
         }
      }
      
      public function SetSkip(param1:Boolean) : void
      {
         this.m_skip = param1;
      }
   }
}

