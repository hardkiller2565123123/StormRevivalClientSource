package net_top_fla
{
   import flash.display.MovieClip;
   import script.icon_item.nut_icon_item;
   import script.net_cmn.smb_menu_off;
   import script.net_cmn.smb_menu_on;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public dynamic class nut_menu_4 extends MovieClip
   {
      
      public var mc_item:nut_icon_item;
      
      public var mc_plate_off:smb_menu_off;
      
      public var mc_plate_on:smb_menu_on;
      
      public var txt_menu:smb_font;
      
      public function nut_menu_4()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_menu.SetTextSize(33);
         this.txt_menu.SetTextFieldWidth(740);
         this.txt_menu.SetTextFit(true);
         if(this.txt_menu.IsArabic() == true)
         {
            this.txt_menu.SetTextPos(this.mc_plate_on.x * 2 - 54,0);
            this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_RC);
         }
         else
         {
            this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_menu.SetTextColor(16774492);
         this.txt_menu.SetDropShadowFilter(6161478);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_menu.SetTextSize(33);
         this.txt_menu.SetTextFieldWidth(740);
         this.txt_menu.SetTextFit(true);
         if(this.txt_menu.IsArabic() == true)
         {
            this.txt_menu.SetTextPos(this.mc_plate_off.x * 2 - 54,0);
            this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_RC);
         }
         else
         {
            this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_menu.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_menu.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame3() : *
      {
         stop();
         this.txt_menu.SetTextSize(33);
         this.txt_menu.SetTextFieldWidth(740);
         this.txt_menu.SetTextFit(true);
         if(this.txt_menu.IsArabic() == true)
         {
            this.txt_menu.SetTextPos(this.mc_plate_on.x * 2 - 54,0);
            this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_RC);
         }
         else
         {
            this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_menu.SetTextColor(7368816);
         this.txt_menu.SetDropShadowFilter(6161478);
      }
      
      internal function frame4() : *
      {
         stop();
         this.txt_menu.SetTextSize(33);
         this.txt_menu.SetTextFieldWidth(740);
         this.txt_menu.SetTextFit(true);
         if(this.txt_menu.IsArabic() == true)
         {
            this.txt_menu.SetTextPos(this.mc_plate_off.x * 2 - 54,0);
            this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_RC);
         }
         else
         {
            this.txt_menu.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_menu.SetTextColor(7368816);
         this.txt_menu.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

