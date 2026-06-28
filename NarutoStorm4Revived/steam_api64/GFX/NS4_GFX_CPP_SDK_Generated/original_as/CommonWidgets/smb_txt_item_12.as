package duel_cond_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol28")]
   public dynamic class smb_txt_item_12 extends MovieClip
   {
      
      public var txt_item:smb_font;
      
      public function smb_txt_item_12()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         if(this.txt_item.IsArabic() == true)
         {
            this.txt_item.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_item.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
         else
         {
            this.txt_item.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_item.SetTextSize(30);
         this.txt_item.SetTextFieldWidth(1300);
         this.txt_item.SetTextFit(true);
         this.txt_item.SetTextColor(smb_font.CCD_COLOR_WHITE);
      }
   }
}

