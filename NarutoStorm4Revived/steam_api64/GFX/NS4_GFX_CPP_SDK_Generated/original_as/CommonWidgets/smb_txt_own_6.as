package start_item_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class smb_txt_own_6 extends MovieClip
   {
      
      public var txt_own:smb_font;
      
      public function smb_txt_own_6()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_own.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_own.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_own.SetTextSize(30);
         if(this.txt_own.IsArabic() == true)
         {
            this.txt_own.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
      }
   }
}

