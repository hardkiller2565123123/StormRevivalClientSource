package net_store_fla
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public dynamic class anm_list_4 extends MovieClip
   {
      
      public var txt_dlc:smb_font;
      
      public var pos:Point;
      
      public function anm_list_4()
      {
         super();
         addFrameScript(0,this.frame1,5,this.frame6,6,this.frame7);
      }
      
      internal function frame1() : *
      {
         this.txt_dlc.SetTextColor(16774492);
         this.txt_dlc.SetTextSize(29);
         this.txt_dlc.SetDropShadowFilter(6358853);
         if(this.txt_dlc.IsArabic() == true)
         {
            this.pos = new Point();
            this.txt_dlc.GetTextPos(this.pos);
            if(this.pos.x < 0)
            {
               this.txt_dlc.SetTextPos(-this.pos.x,this.pos.y);
            }
            this.txt_dlc.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_dlc.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
         else
         {
            this.txt_dlc.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
      }
      
      internal function frame6() : *
      {
         stop();
         this.txt_dlc.SetTextColor(16774492);
         this.txt_dlc.SetTextSize(29);
         this.txt_dlc.SetDropShadowFilter(6358853);
         if(this.txt_dlc.IsArabic() == true)
         {
            this.txt_dlc.GetTextPos(this.pos);
            if(this.pos.x < 0)
            {
               this.txt_dlc.SetTextPos(-this.pos.x,this.pos.y);
            }
            this.txt_dlc.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_dlc.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
         else
         {
            this.txt_dlc.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
      }
      
      internal function frame7() : *
      {
         stop();
         this.txt_dlc.SetTextSize(29);
         this.txt_dlc.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_dlc.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         if(this.txt_dlc.IsArabic() == true)
         {
            this.txt_dlc.GetTextPos(this.pos);
            if(this.pos.x < 0)
            {
               this.txt_dlc.SetTextPos(-this.pos.x,this.pos.y);
            }
            this.txt_dlc.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.txt_dlc.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
         }
         else
         {
            this.txt_dlc.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
      }
   }
}

