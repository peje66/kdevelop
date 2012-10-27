/*
    This file is part of KDevelop
    Copyright 2012 Milian Wolff <mail@milianw.de>
    Copyright (C) 2012  Morten Danielsen Volden mvolden2@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef OUTPUTVIEWTEST_H
#define OUTPUTVIEWTEST_H

#include <QObject>

namespace KDevelop
{
class OutputModel;

class OutputModelTest : public QObject
{
Q_OBJECT
public:
    explicit OutputModelTest(QObject* parent = 0);

private slots:
    void testSetFilteringStrategy();
    void benchmarkAddlinesNofilter();
    void benchmarkAddlinesCompilerfilter();
    void benchmarkAddlinesScriptErrorfilter();
    void benchmarkAddlinesStaticAnalysisfilter();
    void benchAddLongLine();

private:
    void do_currentBench(KDevelop::OutputModel& testee);
};

}
#endif // OUTPUTVIEWTEST_H
