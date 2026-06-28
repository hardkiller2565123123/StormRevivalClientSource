package start_item_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public dynamic class smb_txt_item_7 extends MovieClip
   {
      
      public var txt_item:smb_font;
      
      public function smb_txt_item_7()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_item.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_item.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_item.SetTextSize(30);
         if(this.txt_item.IsArabic() == true)
         {
            this.txt_item.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_item.SetTextPivot(smb_font.CCD_PIVOT_RC);
         }
      }
   }
}

