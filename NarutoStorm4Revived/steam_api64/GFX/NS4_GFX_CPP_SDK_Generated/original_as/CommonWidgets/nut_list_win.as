package script.net_bingo
{
   import InputPad.InputPadKeyCode;
   import Select.UiSelect;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import script.xcmn_font.smb_font;
   import script.xcmn_unset.nut_scb_bg;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol12")]
   public class nut_list_win extends MovieClip
   {
      
      public var all_scb_bar:nut_scb_bg;
      
      public var mc_list00:anm_list;
      
      public var mc_list01:anm_list;
      
      public var mc_list02:anm_list;
      
      public var txt_head:smb_font;
      
      private const CCD_MENU_NUM:uint = 3;
      
      private var m_rewardArr:Array = null;
      
      private var m_select:UiSelect = new UiSelect();
      
      private var m_title:smb_font = null;
      
      private var m_scrBar:nut_scb_bg = null;
      
      private var m_menuArr:Array = new Array();
      
      private var m_cumuAchievementNum:uint = 0;
      
      public function nut_list_win()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_title = this["txt_head"];
         this.m_scrBar = this["all_scb_bar"];
         this.m_menuArr.push(this["mc_list00"]);
         this.m_menuArr.push(this["mc_list01"]);
         this.m_menuArr.push(this["mc_list02"]);
         this.m_title.SetText(String(ExternalInterface.call("MessageConvert","network_sys_198")));
      }
      
      public function SetRewardParamArray(param1:Array, param2:uint) : *
      {
         var _loc5_:Boolean = false;
         this.m_rewardArr = param1;
         var _loc3_:InputPadKeyCode = new InputPadKeyCode();
         this.m_select.InitDispSelect(this.CCD_MENU_NUM,0,0,0,this.m_rewardArr.length - 1,_loc3_.GetKeyInputBtn_L_Up(),_loc3_.GetKeyInputBtn_L_Down(),_loc3_.GetKeyInputBtn_L_Left(),_loc3_.GetKeyInputBtn_L_Right(),UiSelect.CCD_LOOP_TYPE_PUSH);
         var _loc4_:uint = 0;
         while(_loc4_ < this.CCD_MENU_NUM)
         {
            _loc5_ = param2 >= param1[_loc4_].m_cumuAchievementNum ? true : false;
            this.m_menuArr[_loc4_].SetRewardInfo(_loc4_,param1[_loc4_].m_itemId,param1[_loc4_].m_cumuAchievementNum,_loc5_,param1[_loc4_].m_itemNum);
            if(_loc4_ == 0)
            {
               this.m_menuArr[_loc4_].gotoAndStop("on");
            }
            else
            {
               this.m_menuArr[_loc4_].gotoAndStop("off");
            }
            _loc4_++;
         }
         this.m_cumuAchievementNum = param2;
         this.m_scrBar.SetRange(this.m_rewardArr.length,this.CCD_MENU_NUM,false);
         this.m_scrBar.UpdateScroll(0);
      }
      
      public function OnUpdate() : *
      {
         var _loc5_:int = 0;
         var _loc6_:uint = 0;
         var _loc7_:int = 0;
         var _loc8_:Boolean = false;
         var _loc9_:int = 0;
         var _loc1_:int = this.m_select.GetSelValue();
         var _loc2_:int = this.m_select.GetDispSelValue();
         var _loc3_:int = this.m_select.GetDispNo();
         var _loc4_:int = this.m_select.SelectMenuCtrl();
         if(_loc1_ != _loc4_)
         {
            ExternalInterface.call("RequestPlaySE_Select");
            if(_loc3_ != this.m_select.GetDispNo())
            {
               _loc5_ = this.m_select.GetDispNo();
               _loc6_ = 0;
               while(_loc6_ < this.CCD_MENU_NUM)
               {
                  _loc7_ = _loc6_ + _loc5_;
                  if(_loc7_ >= this.m_rewardArr.length || _loc5_ < 0)
                  {
                     ExternalInterface.call("CallAssertFromSwf","BingoBook CumuAchievementRewardWindow[ Not find rewardParam ]");
                  }
                  _loc8_ = this.m_cumuAchievementNum >= this.m_rewardArr[_loc7_].m_cumuAchievementNum ? true : false;
                  this.m_menuArr[_loc6_].SetRewardInfo(_loc7_,this.m_rewardArr[_loc7_].m_itemId,this.m_rewardArr[_loc7_].m_cumuAchievementNum,_loc8_,this.m_rewardArr[_loc7_].m_itemNum);
                  _loc6_++;
               }
               this.m_scrBar.UpdateScroll(_loc5_);
            }
            if(_loc2_ != this.m_select.GetDispSelValue())
            {
               _loc9_ = this.m_select.GetDispSelValue();
               if(_loc9_ >= this.CCD_MENU_NUM || _loc2_ >= this.CCD_MENU_NUM || _loc9_ < 0 || _loc2_ < 0)
               {
                  ExternalInterface.call("CallAssertFromSwf","BingoBook CumuAchievementRewardWindow[ Not find ,menu ]");
               }
               this.m_menuArr[_loc2_].gotoAndStop("off");
               this.m_menuArr[_loc9_].gotoAndStop("on");
            }
         }
      }
      
      internal function frame1() : *
      {
         this.txt_head.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_head.SetTextColor(15058221);
         this.txt_head.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

