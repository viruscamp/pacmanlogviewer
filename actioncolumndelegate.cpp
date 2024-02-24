/**
 * SPDX-FileCopyrightText: 2012 Giuseppe Calà <gcala@mailbox.org>
 *
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "actioncolumndelegate.h"

#include <QPainter>

ActionColumnDelegate::ActionColumnDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QSize ActionColumnDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return option.rect.size();
}

void ActionColumnDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const auto action = index.data().toString();

    const QSize iconSize(22,22);

    const QRect iconRect(option.rect.x() + (option.rect.width()/2) - (iconSize.width()/2),
                   option.rect.y() + (option.rect.height()/2) - (iconSize.height()/2),
                   iconSize.width(),
                   iconSize.height());

    QString icon;
    QString text;

    if(action == "installed") {
        icon = "list-add";
        text = "+";
    } else if(action == "upgraded") {
        icon = "go-up";
        text = "↑";
    } else if(action == "removed") {
        icon = "list-remove";
        text = "-";
    } else if(action == "downgraded") {
        icon = "go-down";
        text = "↓";
    } else if(action == "reinstalled") {
        icon = "view-refresh";
        text = "∓";
    }

    QIcon qicon = QIcon::fromTheme(icon);
    if (qicon.isNull()) {
        // Adwaita icon theme fix
        qicon = QIcon::fromTheme(icon + "-symbolic");
    }

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
        painter->setPen(option.palette.highlightedText().color());
    } else {
        painter->setPen(option.palette.text().color());
    }

	if (qicon.isNull()) {
		// draw text if no icon found
		painter->drawText(iconRect, Qt::AlignCenter, text);
	} else {
        painter->drawPixmap(iconRect, qicon.pixmap(iconSize));
    }
}
