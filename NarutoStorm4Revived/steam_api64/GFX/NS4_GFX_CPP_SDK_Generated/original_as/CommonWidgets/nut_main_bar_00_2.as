package script.option_keyboard
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol24")]
   public dynamic class nut_main_bar_00 extends MovieClip
   {
      
      public var txt_select:smb_font;
      
      public var txt_title:smb_font;
      
      public function nut_main_bar_00()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextFieldWidth(770);
         this.txt_title.SetTextFit(true);
         this.txt_select.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select.SetTextColor(11606272);
         this.txt_select.SetDropShadowFilter(11645361);
         this.txt_select.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
         this.txt_select.SetTextFieldWidth(450);
         this.txt_select.SetTextFit(true);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_select.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select.SetTextColor(11606272);
         this.txt_select.SetDropShadowFilter(11645361);
         this.txt_select.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
      }
      
      internal function frame3() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_select.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select.SetTextColor(16777215);
         this.txt_select.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_select.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
      }
      
      internal function frame4() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetTextColor(6974058);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_select.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_select.SetTextColor(6974058);
         this.txt_select.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_select.SetTextSize(smb_font.CCD_FONT_SIZE_SMALL);
      }
   }
}

