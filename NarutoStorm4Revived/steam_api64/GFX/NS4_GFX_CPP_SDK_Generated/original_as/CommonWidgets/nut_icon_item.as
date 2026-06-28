package script.icon_item
{
   import Enum.Enum_ItemIconLabel;
   import flash.display.MovieClip;
   
   public class nut_icon_item extends MovieClip
   {
      
      public function nut_icon_item()
      {
         super();
      }
      
      public function ChangeItemIcon(param1:int) : *
      {
         var _loc2_:String = null;
         switch(param1)
         {
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_LUNCH_BOX_ATK:
               _loc2_ = "up_atk1";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_LUNCH_BOX_DEF:
               _loc2_ = "up_dif1";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_LUNCH_BOX_CKR:
               _loc2_ = "up_ckr1";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_LUNCH_BOX_STS:
               _loc2_ = "up_sts2";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_LUNCH_BOX_ATK2:
               _loc2_ = "up_atk2";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_USE_ITEM:
               _loc2_ = "cmn_item";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_MOVE_ITEM:
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_COL_OUGI_FINISH:
               _loc2_ = "move";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_EVENT_ITEM:
               _loc2_ = "key_item";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_COL_MOVIE:
               _loc2_ = "movie";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_GIFT_ITEM:
               _loc2_ = "gift";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_COL_MUSIC:
               _loc2_ = "music";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_COL_CARD:
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_COL_CARD_SKIN:
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_COL_NICK_NAME:
               _loc2_ = "card";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_CONV:
               _loc2_ = "conv";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_NONE_ITEM:
               _loc2_ = "none";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_DISCOUNT_1:
               _loc2_ = "dsc_1";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_DISCOUNT_2:
               _loc2_ = "dsc_2";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_DISCOUNT_3:
               _loc2_ = "dsc_3";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_DISCOUNT_5:
               _loc2_ = "dsc_5";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_DISCOUNT_7:
               _loc2_ = "dsc_7";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_DISCOUNT_9:
               _loc2_ = "dsc_9";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_DISCOUNT_10:
               _loc2_ = "dsc_10";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_MONEY:
               _loc2_ = "money";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_COL_KAWARIMI:
               _loc2_ = "kwrm";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_COL_ACCESSORIES:
               _loc2_ = "acc";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_NINGU:
               _loc2_ = "ning";
               break;
            case Enum_ItemIconLabel.CCD_UI_ITEM_DIALOG_ITEM_CATEGORY_CHARA:
               _loc2_ = "char";
         }
         if(_loc2_ != null)
         {
            gotoAndStop(_loc2_);
         }
      }
   }
}

