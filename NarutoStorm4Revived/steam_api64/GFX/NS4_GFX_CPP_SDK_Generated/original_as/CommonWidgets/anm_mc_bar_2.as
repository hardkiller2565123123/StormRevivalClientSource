package script.collect_vo
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.icon_checkbox.nut_checkbox;
   import script.icon_new.nut_new;
   import script.icon_rarity.nut_rarity;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base;
   import script.xcmn_menu.nut_frame_bg;
   import script.xcmn_menu.nut_line;
   import script.xct_deco2.nut_deco2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public class anm_mc_bar extends MovieClip
   {
      
      public static const CCD_PLATE_TYPE_ON:int = 0;
      
      public static const CCD_PLATE_TYPE_OFF:int = 1;
      
      public static const CCD_PLATE_TYPE_ON_CHECK:int = 2;
      
      public static const CCD_PLATE_TYPE_OFF_CHECK:int = 3;
      
      public static const CCD_PLATE_TYPE_NAME:int = 4;
      
      public var all_base:nut_base;
      
      public var all_deco2:nut_deco2;
      
      public var mc_check_1:nut_checkbox;
      
      public var mc_line:nut_line;
      
      public var mc_new_1:nut_new;
      
      public var mc_rarity:nut_rarity;
      
      public var mc_sel:nut_frame_bg;
      
      public var txt_name:smb_font;
      
      public var txt_num:smb_font;
      
      public var txt_vo_1:smb_font;
      
      public var m_name:smb_font = null;
      
      public var m_num:smb_font = null;
      
      public var m_vo_1:smb_font = null;
      
      public var m_new_1:MovieClip = null;
      
      public var m_rearity:MovieClip = null;
      
      public var m_check_1:MovieClip = null;
      
      public var m_deco2:MovieClip = null;
      
      public var m_base:MovieClip = null;
      
      public var m_sel:MovieClip = null;
      
      public var m_line:MovieClip = null;
      
      private var m_plateCenter:Number = 0;
      
      private var m_isChangedLayout:Boolean = false;
      
      public function anm_mc_bar()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_name = smb_font(this["txt_name"]);
         this.m_num = smb_font(this["txt_num"]);
         this.m_vo_1 = smb_font(this["txt_vo_1"]);
         this.m_new_1 = MovieClip(this["mc_new_1"]);
         this.m_rearity = MovieClip(this["mc_rarity"]);
         this.m_check_1 = MovieClip(this["mc_check_1"]);
         this.m_deco2 = MovieClip(this["all_deco2"]);
         this.m_base = MovieClip(this["all_base"]);
         this.m_sel = MovieClip(this["mc_sel"]);
         this.m_line = MovieClip(this["mc_line"]);
         this.m_plateCenter = this.m_base.x;
      }
      
      public function ChangePlate(param1:int, param2:Boolean) : *
      {
         switch(param1)
         {
            case CCD_PLATE_TYPE_ON:
               this.m_name.visible = false;
               this.m_num.visible = true;
               this.m_vo_1.visible = true;
               this.m_new_1.visible = true;
               this.m_rearity.visible = true;
               this.m_check_1.visible = false;
               this.m_deco2.visible = false;
               this.m_base.visible = false;
               this.m_sel.visible = true;
               this.m_line.visible = true;
               this.m_num.SetTextColor(smb_font.CCD_COLOR_BLACK);
               this.m_vo_1.SetTextColor(smb_font.CCD_COLOR_BLACK);
               break;
            case CCD_PLATE_TYPE_OFF:
               this.m_name.visible = false;
               this.m_num.visible = true;
               this.m_vo_1.visible = true;
               this.m_new_1.visible = true;
               this.m_rearity.visible = true;
               this.m_check_1.visible = false;
               this.m_deco2.visible = false;
               this.m_base.visible = false;
               this.m_sel.visible = false;
               this.m_line.visible = true;
               this.m_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
               this.m_vo_1.SetTextColor(smb_font.CCD_COLOR_WHITE);
               break;
            case CCD_PLATE_TYPE_ON_CHECK:
               this.m_name.visible = false;
               this.m_num.visible = true;
               this.m_vo_1.visible = true;
               this.m_new_1.visible = true;
               this.m_rearity.visible = true;
               this.m_check_1.visible = true;
               this.m_deco2.visible = false;
               this.m_base.visible = false;
               this.m_sel.visible = true;
               this.m_line.visible = true;
               this.m_num.SetTextColor(smb_font.CCD_COLOR_BLACK);
               this.m_vo_1.SetTextColor(smb_font.CCD_COLOR_BLACK);
               break;
            case CCD_PLATE_TYPE_OFF_CHECK:
               this.m_name.visible = false;
               this.m_num.visible = true;
               this.m_vo_1.visible = true;
               this.m_new_1.visible = true;
               this.m_rearity.visible = true;
               this.m_check_1.visible = true;
               this.m_deco2.visible = false;
               this.m_base.visible = false;
               this.m_sel.visible = false;
               this.m_line.visible = true;
               this.m_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
               this.m_vo_1.SetTextColor(smb_font.CCD_COLOR_WHITE);
               break;
            case CCD_PLATE_TYPE_NAME:
               this.m_name.visible = true;
               this.m_num.visible = false;
               this.m_vo_1.visible = false;
               this.m_new_1.visible = false;
               this.m_rearity.visible = false;
               this.m_check_1.visible = false;
               this.m_deco2.visible = true;
               this.m_base.visible = true;
               this.m_sel.visible = false;
               this.m_line.visible = false;
         }
         this.m_rearity.visible = false;
         if(param2)
         {
            this.m_rearity.visible = true;
         }
      }
      
      private function CheckArabicLayout() : *
      {
         var _loc1_:Point = null;
         if(this.m_isChangedLayout == true)
         {
            return;
         }
         if(this.m_name.IsArabic() == true)
         {
            this.m_check_1.x += (this.m_plateCenter - this.m_check_1.x) * 2;
            this.m_new_1.x += (this.m_plateCenter - this.m_new_1.x) * 2;
            this.m_rearity.x += (this.m_plateCenter - this.m_rearity.x) * 2;
            this.m_deco2.x += (this.m_plateCenter - this.m_deco2.x) * 2;
            this.m_new_1.scaleX *= -1;
            this.m_base.scaleX *= -1;
            _loc1_ = new Point();
            this.m_name.GetTextPos(_loc1_);
            this.m_name.SetTextPos(_loc1_.x + (this.m_plateCenter - _loc1_.x) * 2,_loc1_.y);
            this.m_num.GetTextPos(_loc1_);
            this.m_num.SetTextPos(_loc1_.x + (this.m_plateCenter - _loc1_.x) * 2,_loc1_.y);
            this.m_vo_1.GetTextPos(_loc1_);
            this.m_vo_1.SetTextPos(_loc1_.x + (this.m_plateCenter - _loc1_.x) * 2,_loc1_.y);
            this.m_name.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_name.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_num.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_vo_1.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_vo_1.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_isChangedLayout = true;
         }
      }
      
      internal function frame1() : *
      {
         this.txt_num.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_num.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_num.SetTextSize(25);
         this.txt_vo_1.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_vo_1.SetTextSize(30);
         this.txt_vo_1.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_vo_1.SetTextFieldWidth(930);
         this.txt_name.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_name.SetTextColor(2374912);
         this.txt_name.SetDropShadowFilter(9999127);
         this.txt_name.SetTextSize(25);
         this.CheckArabicLayout();
         this.stop();
      }
   }
}

