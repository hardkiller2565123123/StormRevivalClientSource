package start_memory_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol50")]
   public dynamic class smb_title00_26 extends MovieClip
   {
      
      public var txt_maintitle:smb_font;
      
      public function smb_title00_26()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_maintitle.SetText("思い出の欠片_gy");
         this.txt_maintitle.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_maintitle.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_maintitle.SetTextSize(30);
         this.txt_maintitle.SetTextFieldWidth(800);
         this.txt_maintitle.SetTextFit(true);
      }
   }
}

