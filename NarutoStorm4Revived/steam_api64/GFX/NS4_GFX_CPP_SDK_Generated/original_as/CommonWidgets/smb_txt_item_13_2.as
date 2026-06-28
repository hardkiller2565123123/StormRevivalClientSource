package start_ning_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol22")]
   public dynamic class smb_txt_item_13 extends MovieClip
   {
      
      public var txt_item:smb_font;
      
      public function smb_txt_item_13()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_item.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_item.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_item.SetTextSize(30);
      }
   }
}

