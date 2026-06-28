package freebtl_prac_lst_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class anm_prac_bar_3 extends MovieClip
   {
      
      public var mc_prac_bar00:MovieClip;
      
      public var mc_check:MovieClip;
      
      public var txt_cmd:smb_font;
      
      public var txt_cnt:smb_font;
      
      public var txt_prac:smb_font;
      
      public function anm_prac_bar_3()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_prac.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_prac.SetTextSize(23);
         this.txt_prac.SetTextColor(16766815);
         this.txt_prac.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_prac.SetTextFieldWidth(240);
         this.txt_prac.SetTextFit(true);
         this.txt_prac.SetTextRubyEnable(true);
         this.txt_cmd.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_cmd.SetTextSize(21);
         this.txt_cmd.SetTextColor(16766815);
         this.txt_cmd.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_cmd.SetTextFieldWidth(450);
         this.txt_cmd.SetTextFit(true);
         this.txt_cmd.SetTextRubyEnable(true);
         this.txt_cnt.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_cnt.SetTextSize(23);
         this.txt_cnt.SetTextColor(16766815);
         this.txt_cnt.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_cnt.SetTextFieldWidth(140);
         this.txt_cnt.SetTextFit(true);
         this.txt_cnt.SetTextRubyEnable(true);
      }
      
      internal function frame2() : *
      {
         this.stop();
         this.txt_prac.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_prac.SetTextSize(23);
         this.txt_prac.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_prac.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_prac.SetTextFieldWidth(240);
         this.txt_prac.SetTextFit(true);
         this.txt_prac.SetTextRubyEnable(true);
         this.txt_cmd.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_cmd.SetTextSize(21);
         this.txt_cmd.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_cmd.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_cmd.SetTextFieldWidth(450);
         this.txt_cmd.SetTextFit(true);
         this.txt_cmd.SetTextRubyEnable(true);
         this.txt_cnt.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_cnt.SetTextSize(23);
         this.txt_cnt.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_cnt.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_cnt.SetTextFieldWidth(140);
         this.txt_cnt.SetTextFit(true);
         this.txt_cnt.SetTextRubyEnable(true);
      }
   }
}

