package script.net_bingo
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.icon_item.nut_icon_item;
   import script.xcmn_font.smb_font;
   import script.xcmn_tex00.nut_tex00;
   import script.xct_maki3.nut_maki_win;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol38")]
   public class anm_detail extends MovieClip
   {
      
      public var all_maki_win:nut_maki_win;
      
      public var dmy_icon_item:nut_tex00;
      
      public var mc_icon_item:nut_icon_item;
      
      public var txt_item:smb_font;
      
      public var txt_num:smb_font;
      
      public var txt_reward:smb_font;
      
      private var m_itemName:smb_font = null;
      
      private var m_itemNum:smb_font = null;
      
      private var m_itemIcon:MovieClip = null;
      
      private var m_itemDmy:MovieClip = null;
      
      private var m_centerPosY:Number = 0;
      
      private var m_isChangedLayout:Boolean = false;
      
      public function anm_detail()
      {
         super();
         addFrameScript(0,this.frame1,4,this.frame5,9,this.frame10);
         this.m_itemName = this["txt_item"];
         this.m_itemNum = this["txt_num"];
         this.m_itemIcon = this["mc_icon_item"];
         this.m_itemDmy = this["dmy_icon_item"];
         var _loc1_:MovieClip = this["txt_reward"];
         if(_loc1_ != null)
         {
            this.m_centerPosY = _loc1_.x;
         }
      }
      
      private function CheckArabicLayout() : *
      {
         var _loc1_:Point = null;
         if(this.m_itemName.IsArabic() == true)
         {
            if(this.m_isChangedLayout == false)
            {
               _loc1_ = new Point();
               this.m_itemName.GetTextPos(_loc1_);
               this.m_itemName.SetTextPos(_loc1_.x + (this.m_centerPosY - _loc1_.x) * 2,_loc1_.y);
               this.m_itemNum.GetTextPos(_loc1_);
               this.m_itemNum.SetTextPos(_loc1_.x + (this.m_centerPosY - _loc1_.x) * 2,_loc1_.y);
               this.m_itemIcon.x += (this.m_centerPosY - this.m_itemIcon.x) * 2;
               this.m_itemDmy.x += (this.m_centerPosY - this.m_itemDmy.x) * 2;
            }
            this.m_itemName.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_itemName.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_itemNum.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_itemNum.SetTextPivot(smb_font.CCD_PIVOT_LC);
            this.m_isChangedLayout = true;
         }
      }
      
      internal function frame1() : *
      {
         this.txt_reward.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_reward.SetTextSize(30);
         this.txt_reward.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_item.SetTextColor(8585987);
         this.txt_item.SetTextSize(28);
         this.txt_item.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_item.SetTextFieldWidth(442);
         this.txt_item.SetTextFit(true);
         this.txt_num.SetTextColor(8585987);
         this.txt_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.CheckArabicLayout();
      }
      
      internal function frame5() : *
      {
         stop();
      }
      
      internal function frame10() : *
      {
         stop();
      }
   }
}

