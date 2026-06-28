package script.net_set
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base4;
   import script.xcmn_menu.nut_base5;
   import script.xcmn_menu.nut_cursor_m;
   import script.xcmn_menu.nut_sel2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public class anm_setbar extends MovieClip
   {
      
      public var all_cursor_m_r:nut_cursor_m;
      
      public var all_base_on:nut_base5;
      
      public var txt_slct:smb_font;
      
      public var all_sel2:nut_sel2;
      
      public var all_base_off:nut_base4;
      
      public var txt_title:smb_font;
      
      public var all_cursor_m_l:nut_cursor_m;
      
      public function anm_setbar()
      {
         var _loc2_:smb_font = null;
         var _loc3_:MovieClip = null;
         var _loc4_:MovieClip = null;
         var _loc5_:Point = null;
         var _loc6_:Number = NaN;
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4,4,this.frame5,5,this.frame6);
         var _loc1_:smb_font = this["txt_title"];
         if(_loc1_ != null && _loc1_.IsArabic() == true)
         {
            _loc2_ = this["txt_slct"];
            _loc3_ = this["all_cursor_m_r"];
            _loc4_ = this["all_cursor_m_l"];
            _loc5_ = new Point();
            _loc1_.GetTextPos(_loc5_);
            _loc1_.SetTextPos(-_loc5_.x,0);
            if(_loc2_ != null)
            {
               _loc2_.GetTextPos(_loc5_);
               _loc2_.SetTextPos(-_loc5_.x,0);
            }
            if(_loc3_ != null && _loc4_ != null)
            {
               _loc6_ = _loc3_.x;
               _loc3_.x = -_loc4_.x;
               _loc4_.x = -_loc6_;
            }
         }
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_slct.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_slct.SetTextColor(11606272);
         this.txt_slct.SetDropShadowFilter(11645361);
         this.txt_slct.SetTextSize(33);
         if(this.txt_title.IsArabic() == true)
         {
            this.txt_title.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_RC);
            if(this.all_base_on.x > 0)
            {
               this.all_base_on.x *= -1;
            }
         }
         else
         {
            this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextSize(33);
         this.txt_title.SetTextFieldWidth(354);
         this.txt_title.SetTextFit(true);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_slct.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_slct.SetTextColor(3355443);
         this.txt_slct.DisableDropShadowFilter();
         this.txt_slct.SetTextSize(33);
         if(this.txt_title.IsArabic() == true)
         {
            this.txt_title.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_RC);
            if(this.all_base_on.x > 0)
            {
               this.all_base_on.x *= -1;
            }
         }
         else
         {
            this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextSize(33);
         this.txt_title.SetTextFieldWidth(354);
         this.txt_title.SetTextFit(true);
      }
      
      internal function frame3() : *
      {
         stop();
         this.txt_slct.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_slct.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_slct.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_slct.SetTextSize(33);
         if(this.txt_title.IsArabic() == true)
         {
            this.txt_title.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_RC);
            if(this.all_base_off.x > 0)
            {
               this.all_base_off.x *= -1;
            }
         }
         else
         {
            this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextSize(33);
         this.txt_title.SetTextFieldWidth(354);
         this.txt_title.SetTextFit(true);
      }
      
      internal function frame4() : *
      {
         stop();
         this.txt_slct.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_slct.SetTextColor(3355443);
         this.txt_slct.DisableDropShadowFilter();
         this.txt_slct.SetTextSize(33);
         if(this.txt_title.IsArabic() == true)
         {
            this.txt_title.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_RC);
            if(this.all_base_off.x > 0)
            {
               this.all_base_off.x *= -1;
            }
         }
         else
         {
            this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextSize(33);
         this.txt_title.SetTextFieldWidth(354);
         this.txt_title.SetTextFit(true);
      }
      
      internal function frame5() : *
      {
         stop();
         if(this.txt_slct.IsArabic() == true)
         {
            this.txt_slct.SetTextPos(-224.6,0);
            if(this.all_base_on.x > 0)
            {
               this.all_base_on.x *= -1;
            }
         }
         else
         {
            this.txt_slct.SetTextPos(224.6,0);
         }
         this.txt_slct.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_slct.SetTextColor(11606272);
         this.txt_slct.SetDropShadowFilter(11645361);
         this.txt_slct.SetTextSize(30);
         this.txt_slct.SetTextFieldWidth(900);
         this.txt_slct.SetTextFit(true);
         if(this.txt_title.IsArabic() == true)
         {
            this.txt_title.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_RC);
         }
         else
         {
            this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextSize(33);
         this.txt_title.SetTextFieldWidth(354);
         this.txt_title.SetTextFit(true);
      }
      
      internal function frame6() : *
      {
         stop();
         if(this.txt_slct.IsArabic() == true)
         {
            this.txt_slct.SetTextPos(-224.6,0);
            if(this.all_base_off.x > 0)
            {
               this.all_base_off.x *= -1;
            }
         }
         else
         {
            this.txt_slct.SetTextPos(224.6,0);
         }
         this.txt_slct.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_slct.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_slct.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_slct.SetTextSize(30);
         this.txt_slct.SetTextFieldWidth(900);
         this.txt_slct.SetTextFit(true);
         if(this.txt_title.IsArabic() == true)
         {
            this.txt_title.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_RC);
         }
         else
         {
            this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         }
         this.txt_title.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextSize(33);
         this.txt_title.SetTextFieldWidth(354);
         this.txt_title.SetTextFit(true);
      }
   }
}

