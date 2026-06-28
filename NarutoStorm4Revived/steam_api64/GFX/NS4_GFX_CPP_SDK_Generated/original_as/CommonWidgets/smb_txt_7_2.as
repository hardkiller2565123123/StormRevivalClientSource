package result_net_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public dynamic class smb_txt_7 extends MovieClip
   {
      
      public var txt_bp:smb_font;
      
      public function smb_txt_7()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_bp.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_bp.SetTextColor(15058221);
         this.txt_bp.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_bp.SetTextFieldWidth(1080);
         this.txt_bp.SetTextFit(true);
      }
   }
}

