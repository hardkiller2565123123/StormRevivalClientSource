package retry_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public dynamic class anm_txtbar_3 extends MovieClip
   {
      
      public var txt_cond:smb_font;
      
      public function anm_txtbar_3()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_cond.SetText("Rozpocznij ponownie walkę z bieżącym poziomem zdrowia przeciwnika");
         this.txt_cond.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_cond.SetTextSize(30);
         this.txt_cond.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_cond.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_cond.SetTextFieldWidth(710);
         this.txt_cond.SetTextFit(true);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_cond.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_cond.SetTextSize(28);
         this.txt_cond.SetTextColor(16514955);
         this.txt_cond.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

