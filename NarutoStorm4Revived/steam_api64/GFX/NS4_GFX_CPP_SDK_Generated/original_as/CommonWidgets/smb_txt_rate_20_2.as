package start_memory_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol44")]
   public dynamic class smb_txt_rate_20 extends MovieClip
   {
      
      public var txt_eval:smb_font;
      
      public function smb_txt_rate_20()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_eval.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_eval.SetTextColor(16776118);
         this.txt_eval.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_eval.SetTextSize(25);
         this.txt_eval.SetTextFieldWidth(300);
         this.txt_eval.SetTextFit(true);
      }
   }
}

