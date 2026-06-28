package script.net_bingo
{
   import InputPad.InputPadKeyCode;
   import KeyHelp.KeyHelpCode;
   import Select.UiSelect;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol42")]
   public class nut_bingo extends MovieClip
   {
      
      private static const CCD_MENU_DETAIL:int = 0;
      
      private static const CCD_MENU_CUMULATIVE:int = 1;
      
      private static const CCD_MENU_NUM:int = 2;
      
      private static const CCD_BOOK_NUM:int = 6;
      
      private static const CCD_ALL_DOWNED:int = 99;
      
      public var all_detail:anm_detail;
      
      public var all_menu00:nut_menu;
      
      public var all_menu01:nut_menu;
      
      public var mc_book1:smb_book1;
      
      public var mc_book2:smb_book1;
      
      public var mc_book3:smb_book1;
      
      public var mc_book4:smb_book1;
      
      public var mc_book5:smb_book1;
      
      public var mc_book6:smb_book1;
      
      private var m_detail:nut_data = null;
      
      private var m_menuArr:Array = new Array();
      
      private var m_bookArr:Array = new Array();
      
      private var m_func:Function = null;
      
      private var m_selectMenu:UiSelect = new UiSelect();
      
      private var m_selectbook:int = 0;
      
      private var m_selectReward:int = 0;
      
      private var m_pad:InputPadKeyCode = new InputPadKeyCode();
      
      private var m_requestCumulative:Boolean = false;
      
      private var m_requestUiEnd:Boolean = false;
      
      private var m_lock:Boolean = true;
      
      private var m_keypush:Boolean = false;
      
      private var m_keyHelp:KeyHelpCode;
      
      private var m_scrollhelppush:Boolean = false;
      
      private var m_select_Back:int = -1;
      
      private var CCD_REWARD_STEP_NONE:int = 0;
      
      private var CCD_REWARD_STEP_IN:int = 1;
      
      private var CCD_REWARD_STEP_WAIT:int = 2;
      
      private var CCD_REWARD_STEP_OUT:int = 3;
      
      private var m_reward_step:int = this.CCD_REWARD_STEP_NONE;
      
      private var m_reward_inout:Boolean = false;
      
      public function nut_bingo()
      {
         super();
         addFrameScript(11,this.frame12,16,this.frame17);
         stop();
         this.m_menuArr.push(this["all_menu00"]);
         this.m_menuArr.push(this["all_menu01"]);
         this.m_bookArr.push(this["mc_book1"]);
         this.m_bookArr.push(this["mc_book2"]);
         this.m_bookArr.push(this["mc_book3"]);
         this.m_bookArr.push(this["mc_book4"]);
         this.m_bookArr.push(this["mc_book5"]);
         this.m_bookArr.push(this["mc_book6"]);
         this.m_selectMenu.InitSelect(0,0,CCD_MENU_NUM - 1,this.m_pad.GetKeyInputBtn_L_Up(),this.m_pad.GetKeyInputBtn_L_Down(),UiSelect.CCD_LOOP_TYPE_PUSH);
         this.m_selectMenu.SetEnablePadOnly(this.m_pad.CCD_PAD_1P);
         this.m_pad.SetEnablePadOnly(this.m_pad.CCD_PAD_1P);
         this.m_menuArr[0].SetText(String(ExternalInterface.call("MessageConvert","network_sys_203")));
         this.m_menuArr[1].SetText(String(ExternalInterface.call("MessageConvert","network_sys_204")));
         this.all_detail.stop();
         this.all_detail.mc_icon_item.visible = false;
         this.all_detail.txt_reward.SetText("");
         this.all_detail.txt_item.SetText("");
         this.all_detail.txt_num.SetText("");
         this.all_detail.dmy_icon_item.Initialize();
         this.all_detail.mc_icon_item.visible = false;
         this.all_detail.dmy_icon_item.visible = false;
         if(this.m_scrollhelppush == false)
         {
            this.m_scrollhelppush = true;
            ExternalInterface.call("PushScrollHelp");
         }
      }
      
      public function OnUpdate() : *
      {
         if(this.m_func != null)
         {
            this.m_func();
         }
         this.UpdateReward();
      }
      
      public function UpdateReward() : *
      {
         var _loc1_:String = null;
         var _loc2_:uint = 0;
         var _loc3_:Array = new Array();
         switch(this.m_reward_step)
         {
            case this.CCD_REWARD_STEP_NONE:
               if(this.m_reward_inout == true)
               {
                  this.all_detail.gotoAndPlay("in");
                  this.all_detail.txt_reward.SetText("");
                  this.all_detail.txt_item.SetText("");
                  this.all_detail.txt_num.SetText("");
                  this.all_detail.dmy_icon_item.DettachImage();
                  this.all_detail.dmy_icon_item.visible = false;
                  this.m_reward_step = this.CCD_REWARD_STEP_IN;
               }
               break;
            case this.CCD_REWARD_STEP_IN:
               if(this.all_detail.currentFrameLabel == "loop")
               {
                  this.all_detail.txt_reward.SetText(String(ExternalInterface.call("MessageConvert","eventcheck_018")));
                  _loc1_ = this.m_bookArr[this.m_selectbook].GetItemName();
                  _loc2_ = uint(this.m_bookArr[this.m_selectbook].GetItemNum());
                  this.all_detail.mc_icon_item.ChangeItemIcon(this.m_bookArr[this.m_selectbook].GetItemCategoryNo());
                  this.all_detail.txt_item.SetText(_loc1_);
                  _loc3_.push("" + _loc2_);
                  this.all_detail.txt_num.SetText(String(ExternalInterface.call("MessageConvert","eventcheck_023")),_loc3_);
                  this.all_detail.dmy_icon_item.DettachImage();
                  trace("## atach :" + this.m_bookArr[this.m_selectReward].GetItemXfbin());
                  this.all_detail.dmy_icon_item.AttachImage(this.m_bookArr[this.m_selectReward].GetItemXfbin());
                  this.all_detail.dmy_icon_item.visible = true;
                  this.m_reward_step = this.CCD_REWARD_STEP_WAIT;
               }
               break;
            case this.CCD_REWARD_STEP_WAIT:
               if(this.m_selectReward != this.m_selectbook)
               {
                  this.m_selectReward = this.m_selectbook;
                  _loc1_ = this.m_bookArr[this.m_selectReward].GetItemName();
                  _loc2_ = uint(this.m_bookArr[this.m_selectReward].GetItemNum());
                  this.all_detail.mc_icon_item.ChangeItemIcon(this.m_bookArr[this.m_selectReward].GetItemCategoryNo());
                  this.all_detail.txt_item.SetText(_loc1_);
                  _loc3_.push("" + _loc2_);
                  this.all_detail.txt_num.SetText(String(ExternalInterface.call("MessageConvert","eventcheck_023")),_loc3_);
                  trace("## atach :" + this.m_bookArr[this.m_selectReward].GetItemXfbin());
                  this.all_detail.dmy_icon_item.AttachImage(this.m_bookArr[this.m_selectReward].GetItemXfbin());
               }
               if(this.m_reward_inout == false)
               {
                  this.all_detail.mc_icon_item.visible = false;
                  this.all_detail.txt_reward.SetText("");
                  this.all_detail.txt_item.SetText("");
                  this.all_detail.txt_num.SetText("");
                  this.all_detail.dmy_icon_item.DettachImage();
                  this.all_detail.dmy_icon_item.visible = false;
                  this.all_detail.gotoAndPlay("out");
                  this.m_reward_step = this.CCD_REWARD_STEP_OUT;
               }
               break;
            case this.CCD_REWARD_STEP_OUT:
               if(this.all_detail.currentFrame >= this.all_detail.totalFrames)
               {
                  this.m_reward_step = this.CCD_REWARD_STEP_NONE;
               }
         }
      }
      
      public function SetBingoBookParam(param1:Array) : *
      {
         var _loc2_:int = 0;
         this.m_keyHelp = new KeyHelpCode();
         this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
         this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
         this.m_keyHelp.PushKeyHelp();
         if(this.m_bookArr.length != param1.length)
         {
            ExternalInterface.call("CallAssertFromSwf","ビンゴブックのパラメータと手配書の数が一致していません");
         }
         else
         {
            _loc2_ = 0;
            this.m_selectbook = CCD_ALL_DOWNED;
            while(_loc2_ < param1.length)
            {
               this.m_bookArr[_loc2_].SetRare(param1[_loc2_].m_rare);
               this.m_bookArr[_loc2_].SetIconCode(param1[_loc2_].m_iconCode);
               this.m_bookArr[_loc2_].SetNameCode(param1[_loc2_].m_nameCode);
               this.m_bookArr[_loc2_].SetItemInfo(param1[_loc2_].m_itemMsg,param1[_loc2_].m_itemNum,param1[_loc2_].m_categoryNo,param1[_loc2_].m_xfbinname);
               if(param1[_loc2_].m_isDowned == true)
               {
                  this.m_bookArr[_loc2_].SetDowned();
               }
               this.m_func = this.StateLoad;
               this.m_selectbook = 0;
               _loc2_++;
            }
         }
      }
      
      public function BackMenuFromCumulative() : *
      {
         if(this.m_keyHelp)
         {
            if(this.m_keypush == true && Boolean(this.m_keyHelp))
            {
               this.m_keyHelp.PopKeyHelp();
               this.m_keypush = false;
            }
            this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
            this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
            this.m_keyHelp.PushKeyHelp();
            this.m_keypush = true;
         }
         this.m_requestCumulative = false;
         gotoAndPlay("in");
         this.m_func = this.StateOpen;
      }
      
      public function IsClosed() : Boolean
      {
         return currentLabel == "end" ? true : false;
      }
      
      public function IsEndUi() : Boolean
      {
         var _loc1_:Boolean = false;
         if(this.m_requestUiEnd == true)
         {
            _loc1_ = currentLabel == "end" ? true : false;
         }
         return _loc1_;
      }
      
      public function IsRequestCumulative() : Boolean
      {
         return this.m_requestCumulative;
      }
      
      private function StateLoad() : *
      {
         var _loc2_:int = 0;
         var _loc1_:int = 0;
         while(_loc1_ < this.m_bookArr.length)
         {
            if(this.m_bookArr[_loc1_].IsLoaded() == false)
            {
               break;
            }
            _loc1_++;
         }
         if(_loc1_ >= this.m_bookArr.length)
         {
            if(this.m_selectbook == CCD_ALL_DOWNED)
            {
               this.m_selectMenu.SetMinValue(CCD_MENU_NUM - 1);
               this.m_selectMenu.SetSelValue(CCD_MENU_NUM - 1);
               this.m_menuArr[0].gotoAndStop("none_off");
            }
            else
            {
               _loc2_ = this.m_selectMenu.GetSelValue();
               _loc1_ = 0;
               while(_loc1_ < CCD_MENU_NUM)
               {
                  if(_loc1_ == _loc2_)
                  {
                     this.m_menuArr[_loc1_].gotoAndStop("on");
                  }
                  else
                  {
                     this.m_menuArr[_loc1_].gotoAndStop("off");
                  }
                  _loc1_++;
               }
            }
            this.m_keypush = true;
            gotoAndPlay("in");
            this.m_func = this.StateOpen;
         }
      }
      
      private function StateOpen() : *
      {
         if(currentLabel == "loop")
         {
            gotoAndStop("loop");
            this.m_func = this.StateSub;
         }
      }
      
      private function StateSub() : *
      {
         var _loc1_:int = 0;
         gotoAndStop("loop");
         _loc1_ = 0;
         while(_loc1_ < this.m_bookArr.length)
         {
            if(this.m_bookArr[_loc1_].GetDowned() == true)
            {
               this.m_bookArr[_loc1_].gotoAndStop("comp_on");
            }
            else
            {
               this.m_bookArr[_loc1_].gotoAndStop("off");
            }
            _loc1_++;
         }
         gotoAndStop("loop");
         _loc1_ = 0;
         while(_loc1_ < this.m_bookArr.length)
         {
            if(this.m_bookArr[_loc1_].GetDowned() == true)
            {
               this.m_bookArr[_loc1_].gotoAndStop("comp_loop");
            }
            _loc1_++;
         }
         this.m_func = this.StateSub2;
      }
      
      private function StateSub2() : *
      {
         var _loc1_:int = 0;
         _loc1_ = 0;
         while(_loc1_ < this.m_bookArr.length)
         {
            if(this.m_bookArr[_loc1_].GetDowned() == true)
            {
               this.m_bookArr[_loc1_].gotoAndStop("comp_on");
            }
            else
            {
               this.m_bookArr[_loc1_].gotoAndStop("off");
            }
            _loc1_++;
         }
         _loc1_ = 0;
         while(_loc1_ < this.m_bookArr.length)
         {
            if(this.m_bookArr[_loc1_].GetDowned() == true)
            {
               this.m_bookArr[_loc1_].gotoAndStop("comp_loop");
            }
            trace("## resettext");
            this.m_bookArr[_loc1_].SetReText();
            _loc1_++;
         }
         this.m_func = this.StateMain;
      }
      
      private function StateMain() : *
      {
         var _loc2_:int = 0;
         if(this.m_lock)
         {
            return;
         }
         this.m_requestCumulative = false;
         if(this.m_select_Back != this.m_selectMenu.GetSelValue())
         {
            this.m_select_Back = this.m_selectMenu.GetSelValue();
            if(this.m_scrollhelppush == false)
            {
               this.m_scrollhelppush = true;
               ExternalInterface.call("PushScrollHelp");
            }
            switch(this.m_selectMenu.GetSelValue())
            {
               case CCD_MENU_DETAIL:
                  ExternalInterface.call("SetScrollHelpId","networkmode_619");
                  break;
               case CCD_MENU_CUMULATIVE:
                  ExternalInterface.call("SetScrollHelpId","networkmode_620");
            }
         }
         var _loc1_:int = int(this.m_pad.GetPadPress());
         if(this.m_pad.GetKeyInputBtn_Ok() & _loc1_)
         {
            ExternalInterface.call("RequestPlaySE_Fix");
            switch(this.m_selectMenu.GetSelValue())
            {
               case CCD_MENU_DETAIL:
                  if(this.m_keyHelp)
                  {
                     if(this.m_keypush == true)
                     {
                        this.m_keyHelp.PopKeyHelp();
                        this.m_keypush = false;
                     }
                     this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
                     this.m_keyHelp.PushKeyHelp();
                     this.m_keypush = true;
                  }
                  if(this.m_selectbook != CCD_ALL_DOWNED)
                  {
                     this.m_selectbook = CCD_ALL_DOWNED;
                     this.m_selectbook = 0;
                     this.m_reward_inout = true;
                     if(this.m_bookArr[this.m_selectbook].GetDowned() == true)
                     {
                        this.m_bookArr[this.m_selectbook].gotoAndStop("comp_on");
                     }
                     else
                     {
                        this.m_bookArr[this.m_selectbook].gotoAndStop("on");
                     }
                     this.m_func = this.StateDetailSelect;
                  }
                  break;
               case CCD_MENU_CUMULATIVE:
                  if(this.m_keyHelp)
                  {
                     if(this.m_keypush == true)
                     {
                        this.m_keyHelp.PopKeyHelp();
                        this.m_keypush = false;
                     }
                     this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
                     this.m_keyHelp.PushKeyHelp();
                     this.m_keypush = true;
                  }
                  gotoAndPlay("out");
                  this.m_requestCumulative = true;
                  this.m_func = this.StateCumulativeMenu;
            }
         }
         else if(this.m_pad.GetKeyInputBtn_Cancel() & _loc1_)
         {
            ExternalInterface.call("RequestPlaySE_Cancel");
            gotoAndPlay("out");
            this.m_requestUiEnd = true;
            this.m_func = this.StateClose;
            if(this.m_keypush == true)
            {
               this.m_keyHelp.PopKeyHelp();
               this.m_keypush = false;
            }
            if(this.m_scrollhelppush == true)
            {
               this.m_scrollhelppush = false;
               ExternalInterface.call("PopScrollHelp");
            }
         }
         else
         {
            _loc2_ = this.m_selectMenu.GetSelValue();
            this.m_selectMenu.SelectMenuCtrl();
            if(_loc2_ != this.m_selectMenu.GetSelValue())
            {
               ExternalInterface.call("RequestPlaySE_Select");
               this.m_menuArr[_loc2_].gotoAndStop("off");
               this.m_menuArr[this.m_selectMenu.GetSelValue()].gotoAndStop("on");
            }
         }
      }
      
      private function StateDetailSelect() : *
      {
         var _loc1_:int = int(this.m_pad.GetPadPress());
         var _loc2_:* = this.m_selectbook;
         if(this.m_pad.GetKeyInputBtn_Cancel() & _loc1_)
         {
            if(this.m_keyHelp)
            {
               if(this.m_keypush == true && Boolean(this.m_keyHelp))
               {
                  this.m_keyHelp.PopKeyHelp();
                  this.m_keypush = false;
               }
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
               this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
               this.m_keyHelp.PushKeyHelp();
               this.m_keypush = true;
            }
            ExternalInterface.call("RequestPlaySE_Cancel");
            if(this.m_bookArr[_loc2_].GetDowned() == true)
            {
               this.m_bookArr[_loc2_].gotoAndStop("comp_loop");
            }
            else
            {
               this.m_bookArr[_loc2_].gotoAndStop("off");
            }
            this.m_func = this.StateMain;
            this.m_reward_inout = false;
            return;
         }
         if(this.m_pad.GetKeyInputBtn_L_Left() & _loc1_)
         {
            if(this.m_selectbook >= 0 && this.m_selectbook <= 2)
            {
               --this.m_selectbook;
               if(this.m_selectbook < 0)
               {
                  this.m_selectbook = 2;
               }
            }
            else
            {
               --this.m_selectbook;
               if(this.m_selectbook < 3)
               {
                  this.m_selectbook = CCD_BOOK_NUM - 1;
               }
            }
         }
         else if(this.m_pad.GetKeyInputBtn_L_Right() & _loc1_)
         {
            if(this.m_selectbook >= 0 && this.m_selectbook <= 2)
            {
               ++this.m_selectbook;
               if(this.m_selectbook > 2)
               {
                  this.m_selectbook = 0;
               }
            }
            else
            {
               ++this.m_selectbook;
               if(this.m_selectbook > 5)
               {
                  this.m_selectbook = 3;
               }
            }
         }
         else if(this.m_pad.GetKeyInputBtn_L_Up() & _loc1_)
         {
            if(this.m_selectbook >= 0 && this.m_selectbook <= 2)
            {
               this.m_selectbook += 3;
            }
            else
            {
               this.m_selectbook -= 3;
            }
         }
         else if(this.m_pad.GetKeyInputBtn_L_Down() & _loc1_)
         {
            if(this.m_selectbook >= 0 && this.m_selectbook <= 2)
            {
               this.m_selectbook += 3;
            }
            else
            {
               this.m_selectbook -= 3;
            }
         }
         if(this.m_selectbook != _loc2_)
         {
            ExternalInterface.call("RequestPlaySE_Select");
            trace("StateDetailSelect::oldSel[" + _loc2_ + "]");
            trace("StateDetailSelect::nowSel[" + this.m_selectbook + "]");
            if(this.m_bookArr[this.m_selectbook].GetDowned() == true)
            {
               this.m_bookArr[this.m_selectbook].gotoAndStop("comp_on");
            }
            else
            {
               this.m_bookArr[this.m_selectbook].gotoAndStop("on");
            }
            if(this.m_bookArr[_loc2_].GetDowned() == true)
            {
               this.m_bookArr[_loc2_].gotoAndStop("comp_loop");
            }
            else
            {
               this.m_bookArr[_loc2_].gotoAndStop("off");
            }
         }
      }
      
      private function StateDetailView() : *
      {
      }
      
      private function StateCumulativeMenu() : *
      {
         trace(" m_requestCumulative " + this.m_requestCumulative);
         if(this.m_requestCumulative == false)
         {
            if(this.m_keypush == true && Boolean(this.m_keyHelp))
            {
               this.m_keyHelp.PopKeyHelp();
               this.m_keypush = false;
            }
            this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_DECIDE);
            this.m_keyHelp.AddKeyHelpTblId(KeyHelpCode.CCD_KEY_HELP_RETURN);
            this.m_keyHelp.PushKeyHelp();
            this.m_keypush = true;
            gotoAndPlay("in");
            this.m_func = this.StateOpen;
         }
      }
      
      private function StateClose() : *
      {
      }
      
      public function SetLock(param1:Boolean) : *
      {
         this.m_lock = param1;
      }
      
      internal function frame12() : *
      {
         stop();
      }
      
      internal function frame17() : *
      {
         stop();
      }
   }
}

