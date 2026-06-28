package result_main_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol136")]
   public dynamic class smb_txt_info_20 extends MovieClip
   {
      
      public var txt_info:smb_font;
      
      public function smb_txt_info_20()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_info.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_info.SetTextSize(28);
         this.txt_info.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_info.SetTextFieldWidth(780);
         this.txt_info.SetTextFit(true);
         this.txt_info.SetText("再戦を申し込まれました_gy■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
      }
   }
}

