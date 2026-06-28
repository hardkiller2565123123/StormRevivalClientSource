package script.net_event
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_line;
   import script.xcp_frame1.smb_xcp_frame1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public class smb_condition_win extends MovieClip
   {
      
      public var all_lst:smb_xcp_frame1;
      
      public var mc_line2:nut_line;
      
      public var txt_reward1:smb_font;
      
      public var txt_reward2:smb_font;
      
      public var txt_title:smb_font;
      
      public var txt_total1:smb_font;
      
      public var txt_total2:smb_font;
      
      private var m_reward_1:smb_font = null;
      
      private var m_reward_2:smb_font = null;
      
      private var m_total_1:smb_font = null;
      
      private var m_total_2:smb_font = null;
      
      private var m_arabicRewardPos_X:Number = 0;
      
      private var m_arabicTotalPos_X:Number = 0;
      
      public function smb_condition_win()
      {
         var _loc1_:Point = null;
         super();
         addFrameScript(0,this.frame1);
         this.m_reward_1 = this["txt_reward1"];
         this.m_reward_2 = this["txt_reward2"];
         this.m_total_1 = this["txt_total1"];
         this.m_total_2 = this["txt_total2"];
         if(this.m_total_1 != null && this.m_reward_1 != null)
         {
            _loc1_ = new Point();
            this.m_total_1.GetTextPos(_loc1_);
            this.m_arabicRewardPos_X = _loc1_.x;
            this.m_reward_1.GetTextPos(_loc1_);
            this.m_arabicTotalPos_X = _loc1_.x;
         }
      }
      
      public function CheckArabic() : *
      {
         var _loc1_:Point = null;
         if(this.m_total_1 != null && this.m_reward_1 != null && this.m_total_2 != null && this.m_reward_2 != null && this.m_total_1.IsArabic() == true)
         {
            _loc1_ = new Point();
            this.m_total_1.GetTextPos(_loc1_);
            this.m_total_1.SetTextPos(this.m_arabicTotalPos_X,_loc1_.y);
            this.m_total_1.SetTextPivot(smb_font.CCD_PIVOT_LC);
            this.m_total_1.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_total_2.GetTextPos(_loc1_);
            this.m_total_2.SetTextPos(this.m_arabicTotalPos_X,_loc1_.y);
            this.m_total_2.SetTextPivot(smb_font.CCD_PIVOT_LC);
            this.m_total_2.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_reward_1.GetTextPos(_loc1_);
            this.m_reward_1.SetTextPos(this.m_arabicRewardPos_X,_loc1_.y);
            this.m_reward_1.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_reward_1.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_reward_2.GetTextPos(_loc1_);
            this.m_reward_2.SetTextPos(this.m_arabicRewardPos_X,_loc1_.y);
            this.m_reward_2.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_reward_2.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
      }
      
      internal function frame1() : *
      {
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetTextSize(28);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_reward1.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_reward1.SetTextSize(30);
         this.txt_total1.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_total1.SetTextSize(30);
         this.txt_reward2.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_reward2.SetTextSize(30);
         this.txt_total2.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_total2.SetTextSize(30);
         this.CheckArabic();
      }
   }
}

