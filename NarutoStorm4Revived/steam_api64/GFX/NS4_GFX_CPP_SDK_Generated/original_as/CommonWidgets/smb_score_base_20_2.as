package freebtl_leag_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public dynamic class smb_score_base_20 extends MovieClip
   {
      
      public var txt_score:smb_font;
      
      public var txt_score_point00:smb_font;
      
      public var txt_score_point01:smb_font;
      
      public var txt_score_title00:smb_font;
      
      public var txt_score_title01:smb_font;
      
      public var txt_win_title:smb_font;
      
      public function smb_score_base_20()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_win_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_win_title.SetTextSize(40);
         this.txt_win_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_win_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_score_title00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_score_title00.SetTextSize(40);
         this.txt_score_title00.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_score_point00.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_score_point00.SetTextSize(40);
         this.txt_score_point00.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_score_title01.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_score_title01.SetTextSize(40);
         this.txt_score_title01.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_score_point01.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_score_point01.SetTextSize(40);
         this.txt_score_point01.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_score.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_score.SetTextSize(40);
         this.txt_score.SetTextColor(smb_font.CCD_COLOR_BLACK);
      }
   }
}

